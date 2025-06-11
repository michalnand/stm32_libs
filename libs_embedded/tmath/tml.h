#ifndef _TML_H_
#define _TML_H_


template<typename DTypeOut, typename DTypeIn, unsigned int M, unsigned int K, unsigned int N>
Matrix<DTypeOut, M, N> gmm(const Matrix<DTypeIn, M, K>& lhs, const Matrix<DTypeIn, K, N>& rhs) 
{
    Matrix<DTypeOut, M, N> result;

    for (unsigned int m = 0; m < M; m++) 
    {
        for (unsigned int n = 0; n < N; n++) 
        {
            DTypeOut sum = 0;
            for (unsigned int k = 0; k < K; k++) 
            {
                sum+= lhs[m*K + k]*rhs[k*N + n];
            }

            result[m*N + n] = sum;
        }
    }
    
    return result;
}


#endif