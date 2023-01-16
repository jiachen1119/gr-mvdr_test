//
// Created by tang on 23-1-13.
//

#ifndef GR_MVDR_TEST_MATLAB_H
#define GR_MVDR_TEST_MATLAB_H


#include <iostream>
#include <mat.h>
#include <cmath>
#include <vector>
#include <armadillo>
class matlab_matRead {
public:
    matlab_matRead(std::string &file_name,std::string &struct_name);
    virtual ~matlab_matRead();
    int calculate_xcor(const matlab_matRead& xcor_array, int target_prn);
    arma::mat getAbsoluteSample(int syncIndex, int prn, int sampleToProcess);
    arma::mat getCarrierPhase(int syncIndex, int prn,int sampleToProcess);

    const std::vector<arma::mat> &getIPsMat() const;
    const std::vector<int> &getPrnData() const;
    const std::vector<arma::mat> &getCarrPhaseMat() const;

private:
    std::string file_name_;
    std::string struct_name_;
    size_t struct_index;

    MATFile *file_array_= nullptr;
    mxArray *struct_array_= nullptr;
    std::vector<mxArray*> prn_array_;
    std::vector<int> prn_data_;
    std::vector<mxArray*> I_Ps_array_;
    std::vector<double> I_Ps_data_;
    std::vector<arma::mat> I_Ps_mat_;
    std::vector<mxArray*> Absolute_sample_array_;
    std::vector<double> Absolute_sample_data_;
    std::vector<arma::mat> Absolute_sample_mat_;
    std::vector<mxArray*> CarrPhase_array_;
    std::vector<double> CarrPhase_data_;
    std::vector<arma::mat> CarrPhase_mat_;

};


#endif // GR_MVDR_TEST_MATLAB_H
