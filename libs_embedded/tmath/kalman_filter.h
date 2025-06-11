#ifndef _KALMAN_FILTER_H_
#define _KALMAN_FILTER_H_

template<typename DType, unsigned int NumStates, unsigned int NumObserved>
class KalmanFilter 
{
    public:
        using StateVec = Matrix<DType, NumStates, 1>;
        using ObsVec   = Matrix<DType, NumObserved, 1>;
        using AType    = Matrix<DType, NumStates, NumStates>;
        using KType    = Matrix<DType, NumStates, NumObserved>;
        using HType    = Matrix<DType, NumObserved, NumStates>;

        KalmanFilter()
        {

        }

        // initialize filter with system matrices (steady state)
        void init(const AType& A_, const KType& K_, const HType& H_, const StateVec& x0) 
        {
            A = A_;
            K = K_;
            H = H_;
            x = x0;
        }   

        void init_from_array(DType *A_, DType *K_, DType *H_, DType *x0) 
        {
            A.from_array(A_);
            K.from_array(K_);
            H.from_array(H_);
            x.from_array(x0);
        }

        // filter step, prediction and correction
        const StateVec& step(ObsVec& z) 
        {
            x = A * x;
            auto error = z - (H * x);
            x = x + K*error;
            
            return x;
        }
        
        // get current state estimate
        StateVec& getState()  
        {
            return x;
        }

    private:
        AType A;    // system matrix
        KType K;    // steady-state Kalman gain
        HType H;    // observation matrix
        StateVec x; // state estimate
};

#endif