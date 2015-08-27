#pragma once

#include <nyutil/vec.hpp>
#include <nyutil/refVec.hpp>

#include <ostream>
#include <iomanip>
#include <cmath>

namespace nyutil
{

template<size_t rows, size_t cols, class prec> class mat;
template<size_t n, class prec> using squareMat = mat<n, n, prec>;

template<class prec> using mat2 = squareMat<2,prec>;
template<class prec> using mat3 = squareMat<3,prec>;
template<class prec> using mat4 = squareMat<4,prec>;

template<class prec> using mat23 = mat<2,3,prec>;
template<class prec> using mat24 = mat<2,4,prec>;
template<class prec> using mat32 = mat<3,2,prec>;
template<class prec> using mat34 = mat<3,4,prec>;
template<class prec> using mat42 = mat<4,2,prec>;
template<class prec> using mat43 = mat<4,3,prec>;

typedef mat2<float> mat2f;
typedef mat2<unsigned int> mat2ui;
typedef mat2<int> mat2i;
typedef mat2<double> mat2d;
typedef mat2<char> mat2c;
typedef mat2<unsigned char> mat2uc;
typedef mat2<long> mat2l;
typedef mat2<unsigned long> mat2ul;
typedef mat2<short> mat2s;
typedef mat2<unsigned short> mat2us;

typedef mat3<float> mat3f;
typedef mat3<unsigned int> mat3ui;
typedef mat3<int> mat3i;
typedef mat3<double> mat3d;
typedef mat3<char> mat3c;
typedef mat3<unsigned char> mat3uc;
typedef mat3<long> mat3l;
typedef mat3<unsigned long> mat3ul;
typedef mat3<short> mat3s;
typedef mat3<unsigned short> mat3us;

typedef mat4<float> mat4f;
typedef mat4<unsigned int> mat4ui;
typedef mat4<int> mat4i;
typedef mat4<double> mat4d;
typedef mat4<char> mat4c;
typedef mat4<unsigned char> mat4uc;
typedef mat4<long> mat4l;
typedef mat4<unsigned long> mat4ul;
typedef mat4<short> mat4s;
typedef mat4<unsigned short> mat4us;



typedef mat23<float> mat23f;
typedef mat23<unsigned int> mat23ui;
typedef mat23<int> mat23i;
typedef mat23<double> mat23d;
typedef mat23<char> mat23c;
typedef mat23<unsigned char> mat23uc;
typedef mat23<long> mat23l;
typedef mat23<unsigned long> mat23ul;
typedef mat23<short> mat23s;
typedef mat23<unsigned short> mat23us;

typedef mat24<float> mat24f;
typedef mat24<unsigned int> mat24ui;
typedef mat24<int> mat24i;
typedef mat24<double> mat24d;
typedef mat24<char> mat24c;
typedef mat24<unsigned char> mat24uc;
typedef mat24<long> mat24l;
typedef mat24<unsigned long> mat24ul;
typedef mat24<short> mat24s;
typedef mat24<unsigned short> mat24us;

typedef mat32<float> mat32f;
typedef mat32<unsigned int> mat32ui;
typedef mat32<int> mat32i;
typedef mat32<double> mat32d;
typedef mat32<char> mat32c;
typedef mat32<unsigned char> mat32uc;
typedef mat32<long> mat32l;
typedef mat32<unsigned long> mat32ul;
typedef mat32<short> mat32s;
typedef mat32<unsigned short> mat32us;

typedef mat34<float> mat34f;
typedef mat34<unsigned int> mat34ui;
typedef mat34<int> mat34i;
typedef mat34<double> mat34d;
typedef mat34<char> mat34c;
typedef mat34<unsigned char> mat34uc;
typedef mat34<long> mat34l;
typedef mat34<unsigned long> mat34ul;
typedef mat34<short> mat34s;
typedef mat34<unsigned short> mat34us;

typedef mat42<float> mat42f;
typedef mat42<unsigned int> mat42ui;
typedef mat42<int> mat42i;
typedef mat42<double> mat42d;
typedef mat42<char> mat42c;
typedef mat42<unsigned char> mat42uc;
typedef mat42<long> mat42l;
typedef mat42<unsigned long> mat42ul;
typedef mat42<short> mat42s;
typedef mat42<unsigned short> mat42us;

typedef mat43<float> mat43f;
typedef mat43<unsigned int> mat43ui;
typedef mat43<int> mat43i;
typedef mat43<double> mat43d;
typedef mat43<char> mat43c;
typedef mat43<unsigned char> mat43uc;
typedef mat43<long> mat43l;
typedef mat43<unsigned long> mat43ul;
typedef mat43<short> mat43s;
typedef mat43<unsigned short> mat43us;


template<size_t rows, size_t cols, class prec> class mat
{
public:
	vec<rows, vec<cols, prec>> data;

public:
	mat() = default;
	~mat() = default;

	mat(const mat<rows, cols, prec>& other) = default;
	mat(mat<rows, cols, prec>&& other) = default;

	mat& operator=(const mat<rows, cols, prec>& other) = default;
	mat& operator=(mat<rows, cols, prec>&& other) = default;

    //operator
	vec<cols, prec>& operator[](size_t i){ return data[i]; }
	const vec<cols, prec>& operator[](size_t i) const { return data[i]; }

	prec& at(size_t row, size_t col){ return data[row][col]; }
	const prec& at(size_t row, size_t col) const { return data[row][col]; }

	vec<cols, prec>& row(size_t i){ return data[i]; }
	const vec<cols, prec>& row(size_t i) const { return data[i]; }

	refVec<cols, prec> col(size_t i){ refVec<rows, prec> ret; for(size_t r(0); r < rows; r++)ret.data[r] = &data[r][i]; return ret; }
	vec<cols, prec> col(size_t i) const { vec<rows, prec> ret; for(size_t r(0); r < rows; r++)ret[r] = data[r][i]; return ret; }

	prec* ptr(){ prec* ret = (prec*) data.data; }
	prec* newPtr(){ prec* ret = new prec[rows * cols]; for(size_t r(0); r < rows; r++)for(size_t c(0); c < cols; c++) ret[r * cols + c] = data[r][c]; }

    mat<rows, cols, prec>& operator +=(const mat<rows, cols, prec>& other){}
   	mat<rows, cols, prec>& operator -=(const mat<rows, cols, prec>& other){}
    mat<rows, cols, prec>& operator *=(const mat<cols, rows, prec>& other){ auto od = data; for(size_t r(0); r < rows; r++) for(size_t c(0); c < cols; c++) data[r][c] = weight(od[r] * other.col(c)); return *this; }
    mat<rows, cols, prec>& operator /=(const mat<cols, rows, prec>& other){}

   	mat<rows, cols, prec>& operator +=(const prec& other){  }
  	mat<rows, cols, prec>& operator -=(const prec& other){  }
    mat<rows, cols, prec>& operator *=(const prec& other){  }
    mat<rows, cols, prec>& operator /=(const prec& other){  }

    mat<cols, rows, prec> flip() const { mat<cols, rows, prec> ret; for(size_t r(0); r < rows; r++) for(size_t c(0); c < cols; c++) ret[c][r] = data[r][c];  return ret; }

    bool isInvertable() const { return 0; }
	mat<cols, rows, prec> inverse() const { mat<cols, rows, prec> ret; return ret; }

    template<class oprec> operator mat<rows, cols, oprec>() const { mat<rows, cols, oprec> ret; for(size_t r(0); r < rows; r++) for(size_t c(0); c < cols; c++) ret[r][c] = data[r][c];  return ret; }
    template<size_t orows, size_t ocols, class oprec> operator mat<orows, ocols, oprec>() const { mat<orows, ocols, oprec> ret; for(size_t r(0); r < std::min(orows, rows); r++) for(size_t c(0); c < std::min(ocols, cols); c++) ret[r][c] = data[r][c];  return ret; }
};

//identityMat
template<size_t dim, typename prec = float> constexpr squareMat<dim, prec> identityMat()
{
	squareMat<dim, prec> ret;
	for(size_t i(0); i < dim; i++) ret[i][i] = prec(1);
	return ret;
}

//operators
//ostream//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
constexpr const unsigned int cDWidth = 6;
constexpr unsigned int getNumberOfDigits(double i)
{
    if((i < 10 && i > 0) || i == 0) return 1;
    else if(i > -10 && i < 0) return 2;
    return i > 0 ? (unsigned int) std::log10((double) i) + 1 : (unsigned int) std::log((double) -i) + 2;
}

template<size_t rows, size_t cols, class prec> std::ostream& operator<<(std::ostream& os, const mat<rows, cols, prec>& obj)
{
    auto org = os.precision();
    os << "{" << "\n";

    for(unsigned int i(0); i < rows; i++)
    {
        os << "  " << "(";
        for(unsigned int o(0); o < cols; o++)
        {
            os << std::setw(cDWidth) << /*std::setprecision(cDWidth - getNumberOfDigits(obj[i][o]) - 1) <<*/ obj[i][o];
            if(o != cols - 1)
                os << ", ";
        }

        os << ")" << "\n";
    }

    os << "}";
    os.precision(org);

    return os;
}

//+////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<size_t rows, size_t cols, typename prec> mat<rows, cols, prec> operator+(mat<rows, cols, prec> ma, const prec& other)
{
    ma *= other;
    return ma;
}


//-////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<size_t rows, size_t cols, typename prec> mat<rows, cols, prec> operator-(mat<rows, cols, prec> ma, const prec& other)
{
    ma -= other;
    return ma;
}


//*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//mat and value
template<size_t rows, size_t cols, typename prec> mat<rows, cols, prec> operator*(mat<rows, cols, prec> ma, const prec& other)
{
    ma *= other;
    return ma;
}

template<size_t rows, size_t cols, typename prec> mat<rows, cols, prec> operator*(const prec& other, mat<rows, cols, prec> ma)
{
    ma *= other;
    return ma;
}

//mat and mat
template<size_t rows, size_t cols, typename prec> mat<rows, cols, prec> operator*(mat<rows, cols, prec> ma, const mat<cols, rows, prec>& other)
{
    ma *= other;
    return ma;
}

//mat and vector
template<size_t dim, typename prec> vec<dim, prec> operator*(const squareMat<dim, prec>& ma, const vec<dim, prec>& v)
{
    vec<dim, prec> ret = v;

    for(size_t i(0); i < dim; i++)
        ret[i] = weight(ma.row(i) * v);

    return ret;
}

template<size_t dim, typename prec> vec<dim, prec> operator*(const vec<dim, prec>& v, const squareMat<dim, prec>& ma)
{
    return (ma * v);
}

//\/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<size_t rows, size_t cols, typename prec> mat<rows, cols, prec> operator/(mat<rows, cols, prec> ma, const prec& other)
{
    ma /= other;
    return ma;
}

} //nyutil
