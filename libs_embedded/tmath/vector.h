#ifndef _Vector_H_
#define _Vector_H_

#include "matrix.h"

// M - num of rows
// N - num of cols
template<class DType, unsigned int N> 
class Vector
{
    public:
        Vector()
        {
  
        }

        Vector(const DType &init_value)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                x[i] = init_value;
            }   
        } 

        Vector(const Vector<DType, N> &rhs)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                x[i] = rhs.x[i];
            } 
        } 

        virtual ~Vector()
        {

        }

    public:
        Vector<DType, N> operator =(const Vector<DType, N> &rhs)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                x[i] = rhs.x[i];
            }

            return *this;
        }   

        DType& operator [](unsigned int idx)
        {
            return x[idx];
        }

    //common operators
    public:
        //two Vector addition
        Vector<DType, N> operator +(Vector<DType, N> rhs)
        {
            Vector<DType, N> result; 

            for (unsigned int i = 0; i < N; i++)
            {
                result[i] = x[i] + rhs[i];
            }

            return result;
        }

        //two Vector substraction
        Vector<DType, N> operator -(Vector<DType, N> rhs)
        {
            Vector<DType, N> result;

            for (unsigned int i = 0; i < N; i++)
            {
                result[i] = x[i] - rhs[i];
            }

            return result;
        }


        //add scalar to Vector
        Vector<DType, N> operator +(DType v)
        {
            Vector<DType, N> result;

            for (unsigned int i = 0; i < N; i++)
            {
                result[i] = x[i] + v;
            }

            return result;
        }

        //subtract scalar from ector
        Vector<DType, N> operator -(DType v)
        {
            Vector<DType, N> result;

            for (unsigned int i = 0; i < N; i++)
            {
                result[i] = x[i] - v;
            }

            return result;
        }

        //multiply by scalar
        Vector<DType, N> operator *(DType v)
        {
            Vector<DType, N> result;

            for (unsigned int i = 0; i < N; i++)
            {
                result[i] = x[i]*v;
            }

            return result;
        }

        
        // element-wise multiplication
        Vector<DType, N> operator *( Vector<DType, N> &rhs)
        {
            Vector<DType, N> result; 

            for (unsigned int n = 0; n < N; n++)
            {
                result[n] = x[n]*rhs[n];
            }

            return result;
        }

        // sum all elements
        DType sum()
        {
            DType result = 0;

            for (unsigned int i = 0; i < N; i++)
            {
                result+=x[i];
            }

            return result;
        }

        // two vectos dot product
        DType dot ( Vector<DType, N> &rhs)
        {
            DType result = 0;

            for (unsigned int n = 0; n < N; n++)
            {
                result+= x[n]*rhs[n];
            }

            return result;
        }

    
    public:
        void init(DType value = 0)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                x[i] = value;
            }
        }

        void from_array(DType *v)
        {
            for (unsigned int i = 0; i < N; i++)
            {
                x[i] = v[i];
            }
        }


        void set(unsigned int idx, DType value)
        {
            x[idx] = value;
        }

        DType get(unsigned int idx)
        {
            return x[idx]; 
        }

        unsigned int size()
        {
            return N;
        }

    //nonlinear operations
    public:
        Vector<DType, N> clip(DType min_v, DType max_v)
        {
            Vector<DType, N> result;

            for (unsigned int i = 0; i < N; i++)
            {
                auto tmp = x[i]; 

                if (tmp < min_v)
                {
                    tmp = min_v;
                }
                else if (tmp > max_v)
                {
                    tmp = max_v;
                }
 
                result[i] = tmp;
            }

            return result;
        }


        Vector<DType, N> shrink(DType min_v, DType max_v)
        {
            Vector<DType, N> result;

            for (unsigned int i = 0; i < N; i++)
            {
                auto tmp = x[i];

                if (tmp < 0 && tmp > min_v)
                {
                    tmp = 0;
                }

                if (tmp > 0 && tmp < max_v)
                {
                    tmp = 0;
                }
 
                result[i] = tmp;
            }

            return result;
        }


        Vector<DType, N> sign()
        {
            Vector<DType, N> result;

            for (unsigned int i = 0; i < N; i++)
            {
                auto tmp = x[i];

                if (tmp < 0)
                {
                    tmp = -1;
                }
                else if (tmp > 0)
                {
                    tmp = -1;
                }
                else
                {
                    tmp = 0;
                }
 
                result[i] = tmp;
            }

            return result;
        }


        Vector<DType, N> abs()
        {
            Vector<DType, N> result;

            for (unsigned int i = 0; i < N; i++)
            {
                auto tmp = x[i];

                if (tmp < 0)
                {
                    tmp = -tmp;
                }
              
                result[i] = tmp;
            }

            return result;
        }

        Vector<DType, N> sqr()
        {
            Vector<DType, N> result;

            for (unsigned int i = 0; i < N; i++)
            {
                auto tmp = x[i];

                result[i] = tmp*tmp;
            }

            return result;
        }
 
    public:     
        template<unsigned int N2> 
        Vector<DType, N + N2> hstack( Vector<DType, N2> &rhs)
        {
            Vector<DType, N + N2> result;

            unsigned int col_ptr = 0;

            for (unsigned int n = 0; n < N; n++)
            {
                result[col_ptr] = x[N + n];
                col_ptr++;
            }

            for (unsigned int n = 0; n < N2; n++)
            {
                result[col_ptr] = rhs[N2 + n];
                col_ptr++;
            } 
            
            return result;
        }

        
        bool all_in_range(DType min_value, DType max_value)
        { 
            for (unsigned int i = 0; i < N; i++) 
            {
                if (x[i] < min_value)
                {
                    return false;
                }

                if (x[i] > max_value)
                {
                    return false;
                }
            }

            return true;
        }

    public:
        Matrix<DType, N, 1> to_row_matrix()
        {
            Matrix<DType, N, 1> result;
            result.from_array(x);

            return result;
        }

        Matrix<DType, 1, N> to_col_matrix()
        {
            Matrix<DType, 1, N> result;
            result.from_array(x);

            return result;
        }

    private:
        DType x[N];
};


#endif