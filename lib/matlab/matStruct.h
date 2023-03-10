//
// Created by tang on 23-1-16.
//

#ifndef GR_MVDR_TEST_MATSTRUCT_H
#define GR_MVDR_TEST_MATSTRUCT_H


#include <armadillo>
struct matStruct{
    int sync_index_;
    double start_sample_;
    arma::mat phase_mat_;
    arma::mat differential_phase_;
    double differential_PhasePeak_;
};


#endif // GR_MVDR_TEST_MATSTRUCT_H
