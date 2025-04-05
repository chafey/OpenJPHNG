#include <openjph/infile_base.h>
#include <openjph/message.h>
#include <openjph/swap_bytes.h>
#include <openjph/wavelet/param_atk.h>

using namespace openjph;
using namespace openjph::wavelet;

namespace openjph
{
namespace wavelet
{


//////////////////////////////////////////////////////////////////////////
const param_atk *param_atk::get_atk(int index) const
{
    const param_atk *p = this;
    while (p && p->get_index() != index)
        p = p->next;
    return p;
}

//////////////////////////////////////////////////////////////////////////
bool param_atk::read_coefficient(infile_base *file, float &K)
{
    int coeff_type = get_coeff_type();
    if (coeff_type == 0)
    { // 8bit
        ui8 v;
        if (file->read(&v, 1) != 1)
            return false;
        K = v;
    }
    else if (coeff_type == 1)
    { // 16bit
        ui16 v;
        if (file->read(&v, 2) != 2)
            return false;
        K = swap_byte(v);
    }
    else if (coeff_type == 2)
    { // float
        union
        {
            float f;
            ui32 i;
        } v;
        if (file->read(&v.i, 4) != 4)
            return false;
        v.i = swap_byte(v.i);
        K = v.f;
    }
    else if (coeff_type == 3)
    { // double
        union
        {
            double d;
            ui64 i;
        } v;
        if (file->read(&v.i, 8) != 8)
            return false;
        v.i = swap_byte(v.i);
        K = (float)v.d;
    }
    else if (coeff_type == 4)
    { // 128 bit float
        ui64 v, v1;
        if (file->read(&v, 8) != 8)
            return false;
        if (file->read(&v1, 8) != 8)
            return false; // v1 not needed
        v = swap_byte(v);

        union
        {
            float f;
            ui32 i;
        } s;
        // convert the MSB of 128b float to 32b float
        // 32b float has 1 sign bit, 8 exponent (offset 127), 23 mantissa
        // 128b float has 1 sign bit, 15 exponent (offset 16383), 112 mantissa
        si32 e = (si32)((v >> 48) & 0x7FFF); // exponent
        e -= 16383;
        e += 127;
        e = e & 0xFF; // removes MSBs if negative
        e <<= 23;     // move bits to their location
        s.i = 0;
        s.i |= ((ui32)(v >> 32) & 0x80000000); // copy sign bit
        s.i |= (ui32)e;                        // copy exponent
        s.i |= (ui32)((v >> 25) & 0x007FFFFF); // copy 23 mantissa
        K = s.f;
    }
    return true;
}


//////////////////////////////////////////////////////////////////////////
bool param_atk::read_coefficient(infile_base *file, si16 &K)
{
    int coeff_type = get_coeff_type();
    if (coeff_type == 0)
    {
        si8 v;
        if (file->read(&v, 1) != 1)
            return false;
        K = v;
    }
    else if (coeff_type == 1)
    {
        si16 v;
        if (file->read(&v, 2) != 2)
            return false;
        K = (si16)swap_byte((ui16)v);
    }
    else
        return false;
    return true;
}

//////////////////////////////////////////////////////////////////////////
bool param_atk::read(infile_base *file)
{
    if (Latk != 0)
    { // this param_atk is used
        param_atk *p = this;
        while (p->next != NULL)
            p = p->next;
        p->next = new param_atk;
        p->alloced_next = true;
        p = p->next;
        return p->read(file);
    }

    if (file->read(&Latk, 2) != 2)
        OJPH_ERROR(0x000500E1, "error reading ATK-Latk parameter");
    Latk = swap_byte(Latk);
    if (file->read(&Satk, 2) != 2)
        OJPH_ERROR(0x000500E2, "error reading ATK-Satk parameter");
    Satk = swap_byte(Satk);
    if (is_m_init0() == false) // only even-indexed is supported
        OJPH_ERROR(0x000500E3,
                   "ATK-Satk parameter sets m_init to 1, "
                   "requiring odd-indexed subsequence in first reconstruction step, "
                   "which is not supported yet.");
    if (is_whole_sample() == false) // ARB filter not supported
        OJPH_ERROR(0x000500E4,
                   "ATK-Satk parameter specified ARB filter, "
                   "which is not supported yet.");
    if (is_reversible() && get_coeff_type() >= 2) // reversible & float
        OJPH_ERROR(0x000500E5,
                   "ATK-Satk parameter does not make sense. "
                   "It employs floats with reversible filtering.");
    if (is_using_ws_extension() == false) // only sym. ext is supported
        OJPH_ERROR(0x000500E6,
                   "ATK-Satk parameter requires constant "
                   "boundary extension, which is not supported yet.");
    if (is_reversible() == false)
        if (read_coefficient(file, Katk) == false)
            OJPH_ERROR(0x000500E7, "error reading ATK-Katk parameter");
    if (file->read(&Natk, 1) != 1)
        OJPH_ERROR(0x000500E8, "error reading ATK-Natk parameter");
    if (Natk > max_steps)
    {
        if (d != d_store) // was this allocated -- very unlikely
            delete[] d;
        d = new lifting_step[Natk];
        max_steps = Natk;
    }

    if (is_reversible())
    {
        for (int s = 0; s < Natk; ++s)
        {
            if (file->read(&d[s].rev.Eatk, 1) != 1)
                OJPH_ERROR(0x000500E9, "error reading ATK-Eatk parameter");
            if (file->read(&d[s].rev.Batk, 2) != 2)
                OJPH_ERROR(0x000500EA, "error reading ATK-Batk parameter");
            d[s].rev.Batk = (si16)swap_byte((ui16)d[s].rev.Batk);
            ui8 LCatk;
            if (file->read(&LCatk, 1) != 1)
                OJPH_ERROR(0x000500EB, "error reading ATK-LCatk parameter");
            if (LCatk == 0)
                OJPH_ERROR(0x000500EC,
                           "Encountered a ATK-LCatk value of zero; "
                           "something is wrong.");
            if (LCatk > 1)
                OJPH_ERROR(0x000500ED,
                           "ATK-LCatk value greater than 1; "
                           "that is, a multitap filter is not supported");
            if (read_coefficient(file, d[s].rev.Aatk) == false)
                OJPH_ERROR(0x000500EE, "Error reding ATK-Aatk parameter");
        }
    }
    else
    {
        for (int s = 0; s < Natk; ++s)
        {
            ui8 LCatk;
            if (file->read(&LCatk, 1) != 1)
                OJPH_ERROR(0x000500EF, "error reading ATK-LCatk parameter");
            if (LCatk == 0)
                OJPH_ERROR(0x000500F0,
                           "Encountered a ATK-LCatk value of zero; "
                           "something is wrong.");
            if (LCatk > 1)
                OJPH_ERROR(0x000500F1,
                           "ATK-LCatk value greater than 1; "
                           "that is, a multitap filter is not supported.");
            if (read_coefficient(file, d[s].irv.Aatk) == false)
                OJPH_ERROR(0x000500F2, "Error reding ATK-Aatk parameter");
        }
    }

    return true;
}

//////////////////////////////////////////////////////////////////////////
void param_atk::init_irv97()
{
    Satk = 0x4a00; // illegal because ATK = 0
    Katk = (float)1.230174104914001;
    Natk = 4;
    // next is (A-4) in T.801 second line
    Latk = (ui16)(5 + Natk + sizeof(float) * (1 + Natk));
    d[0].irv.Aatk = (float)0.443506852043971;
    d[1].irv.Aatk = (float)0.882911075530934;
    d[2].irv.Aatk = (float)-0.052980118572961;
    d[3].irv.Aatk = (float)-1.586134342059924;
}

//////////////////////////////////////////////////////////////////////////
void param_atk::init_rev53()
{
    Satk = 0x5801; // illegal because ATK = 1
    Natk = 2;
    // next is (A-4) in T.801 fourth line
    Latk = (ui16)(5 + 2 * Natk + sizeof(ui8) * (Natk + Natk));
    d[0].rev.Aatk = 1;
    d[0].rev.Batk = 2;
    d[0].rev.Eatk = 2;
    d[1].rev.Aatk = -1;
    d[1].rev.Batk = 1;
    d[1].rev.Eatk = 1;
}

} // namespace wavelet
} // namespace openjph