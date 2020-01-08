#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
#pragma GCC optimize("O3")
#pragma GCC optimize("unroll-loops")
//#define int long long
using namespace std;
using ll = long long;
using pii = pair<int, int>;
const int INF = 987654321;
const int MOD = 1e9 + 7;

using cp = complex<long double>;
using func = vector<cp>;
class FastFourierTransform
{
private:
    const double PI = acos(-1);

    void FFT(func &f, cp w)
    {
        int n = f.size();
        if (n == 1)
            return;

        func even(n / 2), odd(n / 2);
        for (int i = 0; i < n; i++)
            (i & 1 ? odd : even)[i / 2] = f[i];

        FFT(even, w * w);
        FFT(odd, w * w);

        cp wp(1, 0);
        for (int i = 0; i < n / 2; i++)
        {
            f[i] = even[i] + wp * odd[i];
            f[i + n / 2] = even[i] - wp * odd[i];
            wp *= w;
        }
    }

public:
    func multiply(func f, func g)
    {
        int sz = f.size() + g.size() - 1;
        int n = 1;
        while (n < f.size() + 1 || n < g.size() + 1)
            n *= 2;
        n *= 2;
        func h(n);
        f.resize(n);
        g.resize(n);

        cp w(cos(2 * PI / n), sin(2 * PI / n));

        FFT(f, w);
        FFT(g, w);

        for (int i = 0; i < n; i++)
            h[i] = f[i] * g[i];

        FFT(h, cp(1, 0) / w);
        for (int i = 0; i < n; i++)
        {
            h[i] /= cp(n, 0);
            h[i] = cp(round(h[i].real()), round(h[i].imag()));
        }

        while (h.size() != sz)
            h.pop_back();

        return h;
    }
};

class CrazyInt
{
protected:
    bool isNegative;
    uint32_t *byte;
    uint32_t size;
    static uint32_t KARATSUBA_BOUND;

    void clear()
    {
        isNegative = false;
        if (size)
        {
            size = 0;
            if (byte)
            {
                delete[] byte;
                byte = nullptr;
            }
        }
    }
    void resize(int32_t sz)
    {
        if (size < 0)
        {
            return;
        }
        if (size)
        {
            size = 0;
            if (byte)
            {
                delete[] byte;
                byte = nullptr;
            }
        }
        size = sz;
        if (sz)
            byte = new uint32_t[sz]();
    }

    void expand(int32_t sz = 0)
    {
        if (!sz)
            sz = size * 2;

        uint32_t *newByte = new uint32_t[sz]();
        std::copy(byte, byte + std::min(size, (uint32_t)sz), newByte);

        size = sz;
        if (byte)
        {
            delete[] byte;
            byte = nullptr;
        }
        byte = newByte;
    }

    void shrink()
    {
        if (size)
        {
            while (size && !byte[size - 1])
                size--;
            if (!size)
            {
                if (byte)
                    delete[] byte;
                byte = nullptr;
            }
        }
    }

public:
    class OneBit
    {
        uint32_t mask;
        uint32_t &orgBits;

    public:
        OneBit(const uint32_t &offset, uint32_t &orgBits) : mask((unsigned long long)1 << offset), orgBits(orgBits) {}
        ~OneBit() {}
        operator bool() const
        {
            return (unsigned long long)orgBits & mask;
        }
        const bool operator=(const bool &rb)
        {
            return (orgBits = (unsigned long long)orgBits ^ ((orgBits & mask) == !!rb ? 0 : mask));
        }
    };

    CrazyInt() : isNegative(false), byte(nullptr), size(0) {}
    CrazyInt(const int &rb) : CrazyInt() { *this = (long long)rb; }
    CrazyInt(const float &rb) : CrazyInt() { *this = (long long)rb; }
    CrazyInt(const double &rb) : CrazyInt() { *this = (long long)rb; }
    CrazyInt(const long long &rb) : CrazyInt() { *this = rb; }

    CrazyInt(const std::string &rb) : CrazyInt() { *this = rb; }

    CrazyInt(const CrazyInt &rb) : CrazyInt() { *this = rb; }

    ~CrazyInt()
    {
        if (size)
        {
            size = 0;
        }
        if (byte)
            delete[] byte;
        byte = nullptr;
    }

    static void setKaratsubaBound(uint32_t newBound) { KARATSUBA_BOUND = newBound; }

    uint32_t byteSize() const { return size; }
    bool isZero() const { return !size; }

    void _toString(bool fillZero, uint32_t currDivSiz, std::ostringstream &stream) const
    {
        if (size <= 1)
        {
            if (fillZero)
                stream << std::setw(currDivSiz) << std::setfill('0');
            if (size == 1)
                stream << byte[0];
            else
                stream << 0;
            return;
        }
        CrazyInt currDivisor = 1;
        uint32_t cnt = currDivSiz / 2;
        while (cnt--)
        {
            currDivisor = (currDivisor << 1) + (currDivisor << 3);
        }
        auto divide = divmod(currDivisor);

        divide.first._toString(fillZero, currDivSiz - currDivSiz / 2, stream);
        divide.second._toString(true, currDivSiz / 2, stream);
    }

    std::string toString() const
    {
        if (isNegative)
            return "-" + (-(*this)).toString();
        if (size == 1)
            return std::to_string(byte[0]);

        CrazyInt currDivisor = 1;
        uint32_t currDivSiz = 0;
        std::ostringstream str;

        while (!(currDivisor > *this))
        {
            currDivisor = (currDivisor << 4) + (currDivisor << 8) + (currDivisor << 9) + (currDivisor << 10) + (currDivisor << 13);
            currDivSiz += 4;
        }

        _toString(false, currDivSiz, str);
        return str.str();
    }

    OneBit operator[](const uint32_t &rb)
    {
        if (rb / 32 + 1 > size)
            expand(rb / 32 + 1);
        OneBit ret(rb % 32, byte[rb / 32]);
        return ret;
    }

    const bool operator[](const uint32_t &rb) const
    {
        return ((unsigned long long)byte[rb / 32] >> (rb % 32)) & 1;
    }

    CrazyInt &operator=(const CrazyInt &rb)
    {
        if (this == &rb)
            return *this;

        clear();

        resize(rb.size);
        this->isNegative = rb.isNegative;

        std::copy(rb.byte, rb.byte + rb.size, byte);
        return *this;
    }

    CrazyInt &operator=(const long long &rb)
    {
        clear();

        uint32_t rbSize = 0, currIdx = 0;
        unsigned long long val;

        isNegative = rb < 0;

        val = rb > 0 ? rb : -rb;

        while (val)
        {
            rbSize++;
            val >>= 32;
        }

        resize(rbSize);

        val = rb > 0 ? rb : -rb;

        while (val)
        {
            byte[currIdx++] = val & UINT32_MAX;
            val >>= 32;
        }

        return *this;
    }

    CrazyInt &operator=(const std::string &rb)
    {
        clear();

        uint32_t currIdx, stringLength;
        CrazyInt currVal;

        std::string trimmed = rb;
        trimmed.erase(0, trimmed.find_first_not_of("\t\n\v\f\r "));
        trimmed.erase(trimmed.find_last_not_of("\t\n\v\f\r ") + 1);

        isNegative = (trimmed[0] == '-');
        currIdx = (trimmed[0] == '-' || trimmed[0] == '+');
        stringLength = trimmed.length();
        currVal = 0;

        while (currIdx < stringLength)
        {
            currVal = (currVal << 1) + (currVal << 3);
            currVal += rb[currIdx] - '0';
            currIdx++;
        }

        return *this = currVal;
    }

    bool operator==(const CrazyInt &rb) const
    {
        if (size != rb.size)
            return false;
        for (uint32_t currIdx = 0; currIdx < rb.size; currIdx++)
        {
            if (this->byte[currIdx] != rb.byte[currIdx])
                return false;
        }
        return true;
    }

    bool operator>(const CrazyInt &rb) const
    {

        if (!isNegative && rb.isNegative)
            return true;
        if (isNegative && !rb.isNegative)
            return false;
        if (isNegative && rb.isNegative)
            return -*this < -rb;

        if (size > rb.size)
            return true;
        if (size < rb.size)
            return false;
        if (!size && !rb.size)
            return false;

        for (uint32_t currIdx = rb.size - 1; currIdx > 0; currIdx--)
        {
            if (this->byte[currIdx] > rb.byte[currIdx])
                return true;
            if (this->byte[currIdx] < rb.byte[currIdx])
                return false;
        }
        return this->byte[0] > rb.byte[0];
    }

    bool operator<(const CrazyInt &rb) const
    {

        if (!isNegative && rb.isNegative)
            return false;
        if (isNegative && !rb.isNegative)
            return true;
        if (isNegative && rb.isNegative)
            return -*this < -rb;

        if (size > rb.size)
            return false;
        if (size < rb.size)
            return true;
        if (!size && !rb.size)
            return false;

        for (uint32_t currIdx = rb.size - 1; currIdx > 0; currIdx--)
        {
            if (this->byte[currIdx] < rb.byte[currIdx])
                return true;
            if (this->byte[currIdx] > rb.byte[currIdx])
                return false;
        }
        return this->byte[0] < rb.byte[0];
    }

    bool operator!=(const CrazyInt &rb) const
    {
        return !(*this == rb);
    }
    bool operator>=(const CrazyInt &rb) const
    {
        return !(*this < rb);
    }
    bool operator<=(const CrazyInt &rb) const
    {
        return !(*this > rb);
    }

    const CrazyInt operator-() const
    {
        CrazyInt ret = *this;
        ret.isNegative ^= 1;
        return ret;
    }

    CrazyInt &operator<<=(const int32_t &rb)
    {
        if (size == 0 || rb == 0)
        {
            return *this;
        }
        if (rb < 0)
        {
            return *this >>= (-rb);
        }
        if (rb > 32 && rb % 32)
        {
            return (*this <<= (rb % 32)) <<= (rb - rb % 32);
        }
        if (rb % 32)
        {
            unsigned long long tempVal = 0, tempByte;
            uint32_t currIdx = 0;

            expand(size + 1);

            while (currIdx < size - 1)
            {
                tempByte = (((unsigned long long)byte[currIdx] << rb) & UINT32_MAX) + tempVal;
                tempVal = (unsigned long long)byte[currIdx] >> (32 - rb);
                byte[currIdx] = tempByte & UINT32_MAX;
                currIdx++;
            }
            byte[currIdx] = tempVal & UINT32_MAX;
            shrink();

            return *this;
        }
        else
        {
            uint32_t shiftByte = rb / 32;

            expand(size + shiftByte);
            std::copy_backward(byte, byte + size - shiftByte, byte + size);
            std::fill(byte, byte + shiftByte, 0);

            return *this;
        }
    }

    CrazyInt &operator>>=(const int32_t &rb)
    {
        if (size == 0 || rb == 0)
        {
            return *this;
        }
        if (rb < 0)
        {
            return *this <<= (-rb);
        }
        if (rb > 32 && rb % 32)
        {
            return (*this >>= (rb % 32)) >>= (rb - rb % 32);
        }
        if (rb % 32)
        {
            unsigned long long tempVal = 0, tempByte;
            uint32_t currIdx = size - 1;

            while (currIdx > 0)
            {
                tempByte = ((tempVal + byte[currIdx]) >> rb) & UINT32_MAX;
                tempVal = ((unsigned long long)byte[currIdx] & (((unsigned long long)1 << rb) - 1)) << 32;
                byte[currIdx] = tempByte & UINT32_MAX;
                currIdx--;
            }
            byte[currIdx] = ((tempVal + byte[currIdx]) >> rb) & UINT32_MAX;
            shrink();

            return *this;
        }
        else
        {
            uint32_t shiftByte = rb / 32;

            std::copy(byte + shiftByte, byte + size, byte);
            expand(size - shiftByte);

            return *this;
        }
    }

    CrazyInt &operator+=(const CrazyInt &rb)
    {

        unsigned long long tempVal = 0, tempByte;
        uint32_t currIdx;

        if (*this < rb)
        {
            //return *this = (CrazyInt(rb) += *this);
            uint32_t orgSize = size;
            expand(rb.size + 1);

            for (currIdx = 0; currIdx < orgSize; currIdx++)
            {
                tempByte = ((tempVal + rb.byte[currIdx]) + byte[currIdx]) & UINT32_MAX;
                tempVal = ((tempVal + rb.byte[currIdx]) + byte[currIdx]) >> 32;
                byte[currIdx] = tempByte & UINT32_MAX;
            }

            for (; currIdx < size - 1; currIdx++)
            {
                tempByte = (tempVal + rb.byte[currIdx]) & UINT32_MAX;
                tempVal = (tempVal + rb.byte[currIdx]) >> 32;
                byte[currIdx] = tempByte & UINT32_MAX;
            }
            byte[currIdx] = tempVal & UINT32_MAX;
            shrink();

            return *this;
        }

        expand(size + 1);

        for (currIdx = 0; currIdx < rb.size; currIdx++)
        {
            tempByte = ((tempVal + byte[currIdx]) + rb.byte[currIdx]) & UINT32_MAX;
            tempVal = ((tempVal + byte[currIdx]) + rb.byte[currIdx]) >> 32;
            byte[currIdx] = tempByte & UINT32_MAX;
        }

        for (; currIdx < size - 1; currIdx++)
        {
            tempByte = (tempVal + byte[currIdx]) & UINT32_MAX;
            tempVal = (tempVal + byte[currIdx]) >> 32;
            byte[currIdx] = tempByte & UINT32_MAX;
        }
        byte[currIdx] = tempVal & UINT32_MAX;
        shrink();

        return *this;
    }

    CrazyInt &operator-=(const CrazyInt &rb)
    {

        if (*this < rb)
        {
            return *this = -(CrazyInt(rb) -= *this);
        }

        uint32_t currIdx = 0;

        while (currIdx < rb.size)
        {
            if (byte[currIdx] < rb.byte[currIdx])
            {
                uint32_t borrowIdx = currIdx + 1;
                while (!byte[borrowIdx])
                {
                    borrowIdx++;
                }
                byte[borrowIdx]--;
                while (--borrowIdx > currIdx)
                    byte[borrowIdx] = UINT32_MAX;
                byte[currIdx] = (((unsigned long long)UINT32_MAX + 1 - rb.byte[currIdx]) + byte[currIdx]) & UINT32_MAX;
            }
            else
            {
                byte[currIdx] -= rb.byte[currIdx];
            }
            currIdx++;
        }
        shrink();

        return *this;
    }

    CrazyInt &operator*=(const CrazyInt &rb)
    {
        if (*this < rb)
        {
            return *this = (CrazyInt(rb) *= (*this));
        }

        if (rb.size < KARATSUBA_BOUND)
        {
            CrazyInt cur = *this, rbCopy;
            uint32_t currIdx = 0;

            isNegative ^= rb.isNegative;

            rbCopy = rb;
            *this = 0;

            while (currIdx < rbCopy.size * 32)
            {
                if (rbCopy[currIdx])
                {
                    *this += cur;
                }
                cur <<= 1;
                currIdx++;
            }
        }
        else
        {
            CrazyInt x0, x1, y0, y1;
            CrazyInt z0, z1, z2;
            unsigned int M = size / 2;

            x1 = *this >> M * 32;
            y1 = rb >> M * 32;

            x0.resize(M);
            y0.resize(M);

            std::copy(byte, byte + M, x0.byte);
            if (rb.size > M)
                std::copy(rb.byte, rb.byte + M, y0.byte);

            z0 = x0 * y0;
            z2 = x1 * y1;
            z1 = (x1 + x0) * (y1 + y0) - (z0 + z2);

            *this = (((z2 << M * 32) + z1) << M * 32) + z0;
        }

        shrink();
        return *this;
    }

    CrazyInt &operator/=(const CrazyInt &rb)
    {
        if (*this < rb)
        {
            return *this = CrazyInt(0);
        }
        if (rb == 0)
        {
            return *this = 0;
        }

        CrazyInt rem = *this;
        CrazyInt currRb;

        uint32_t currIdx = (size - rb.size + 1) * 32 - 1;
        uint32_t preCalculated = 0;

        isNegative ^= rb.isNegative;
        currRb = rb << currIdx;

        resize(size - rb.size + 1);

        while (true)
        {
            if (rem >= currRb)
            {
                rem -= currRb;
                preCalculated |= ((unsigned long long)1 << (currIdx % 32)) & UINT32_MAX;
            }
            if (!(currIdx % 32))
            {
                byte[currIdx / 32] = preCalculated;
                preCalculated = 0;
                if (rem.isZero())
                    break;
            }

            if (!currIdx)
                break;
            currIdx--;
            currRb >>= 1;
        }
        shrink();

        return *this;
    }

    CrazyInt &operator%=(const CrazyInt &rb)
    {
        if (*this < 0)
        {
            return *this = -(CrazyInt(-*this) %= rb);
        }
        if (rb < 0)
        {
            return *this = CrazyInt(*this) %= (-rb);
        }
        if (*this < rb)
        {
            return *this;
        }

        CrazyInt currRb;
        CrazyInt rem = *this;

        uint32_t currIdx = (size - rb.size + 1) * 32 - 1;
        currRb = rb << currIdx;

        while (true)
        {
            if (rem >= currRb)
            {
                rem -= currRb;
                if (rem.isZero())
                    break;
            }
            if (!currIdx)
                break;
            currIdx--;
            currRb >>= 1;
        }
        rem.shrink();

        return *this = rem;
    }

    std::pair<CrazyInt, CrazyInt> divmod(const CrazyInt &rb) const
    {
        if (*this < rb)
        {
            return std::pair<CrazyInt, CrazyInt>(CrazyInt(0), CrazyInt(rb));
        }

        CrazyInt divisor;
        CrazyInt rem = *this;
        CrazyInt currRb;

        uint32_t currIdx = (size - rb.size + 1) * 32 - 1;
        uint32_t preCalculated = 0;

        divisor.isNegative = isNegative ^ rb.isNegative;
        currRb = rb << currIdx;

        divisor.resize(size - rb.size + 1);

        while (true)
        {
            if (rem >= currRb)
            {
                rem -= currRb;
                preCalculated |= ((unsigned long long)1 << (currIdx % 32)) & UINT32_MAX;
            }
            if (!(currIdx % 32))
            {
                divisor.byte[currIdx / 32] = preCalculated;
                preCalculated = 0;
                if (rem.isZero())
                    break;
            }
            if (!currIdx)
                break;
            currIdx--;
            currRb >>= 1;
        }
        divisor.shrink();

        return std::pair<CrazyInt, CrazyInt>(divisor, rem);
    }

    CrazyInt &operator&=(const CrazyInt &rb)
    {

        uint32_t currIdx;

        if (*this < rb)
        {
            return *this = (CrazyInt(rb) += *this);
        }

        expand(rb.size);

        for (currIdx = 0; currIdx < rb.size; currIdx++)
        {
            byte[currIdx] = (byte[currIdx] & rb.byte[currIdx]) & UINT32_MAX;
        }

        return *this;
    }

    CrazyInt &operator|=(const CrazyInt &rb)
    {

        uint32_t currIdx;

        if (*this < rb)
        {
            return *this = (CrazyInt(rb) += *this);
        }

        for (currIdx = 0; currIdx < rb.size; currIdx++)
        {
            byte[currIdx] = (byte[currIdx] | rb.byte[currIdx]) & UINT32_MAX;
        }
        shrink();

        return *this;
    }

    CrazyInt &operator^=(const CrazyInt &rb)
    {

        uint32_t currIdx;

        if (*this < rb)
        {
            return *this = (CrazyInt(rb) += *this);
        }

        for (currIdx = 0; currIdx < rb.size; currIdx++)
        {
            byte[currIdx] = (byte[currIdx] ^ rb.byte[currIdx]) & UINT32_MAX;
        }
        shrink();

        return *this;
    }

    const CrazyInt operator<<(const int32_t &rb) const
    {
        return CrazyInt(*this) <<= rb;
    }
    const CrazyInt operator>>(const int32_t &rb) const
    {
        return CrazyInt(*this) >>= rb;
    }
    const CrazyInt operator+(const CrazyInt &rb) const
    {
        return CrazyInt(*this) += rb;
    }
    const CrazyInt operator-(const CrazyInt &rb) const
    {
        return CrazyInt(*this) -= rb;
    }
    const CrazyInt operator*(const CrazyInt &rb) const
    {
        return CrazyInt(*this) *= rb;
    }
    const CrazyInt operator/(const CrazyInt &rb) const
    {
        return CrazyInt(*this) /= rb;
    }
    const CrazyInt operator%(const CrazyInt &rb) const
    {
        return CrazyInt(*this) %= rb;
    }
    const CrazyInt operator&(const CrazyInt &rb) const
    {
        return CrazyInt(*this) &= rb;
    }
    const CrazyInt operator|(const CrazyInt &rb) const
    {
        return CrazyInt(*this) |= rb;
    }
    const CrazyInt operator^(const CrazyInt &rb) const
    {
        return CrazyInt(*this) ^= rb;
    }
};
uint32_t CrazyInt::KARATSUBA_BOUND = 24;

std::istream &operator>>(std::istream &is, CrazyInt &rb)
{
    std::string tempString;
    is >> tempString;
    rb = tempString;
    return is;
}
std::ostream &operator<<(std::ostream &os, const CrazyInt &rb)
{
    os << rb.toString();
    return os;
}

main()
{
    cin.tie(0);
    ios::sync_with_stdio(0);
    FastFourierTransform FFT;

    func f, g;
    int n, m;
    cin >> n >> m;
    for (int i = 0; i <= n; i++)
    {
        int x;
        cin >> x;
        f.push_back(x);
    }

    for (int i = 0; i <= m; i++)
    {
        int x;
        cin >> x;
        g.push_back(x);
    }

    CrazyInt ans(0);
    for (auto i : FFT.multiply(f, g))
    {
        string s = to_string(i.real());
        ans ^= CrazyInt(s.substr(0, s.find('.')));
    }
    cout << ans;
}