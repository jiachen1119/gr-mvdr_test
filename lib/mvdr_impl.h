/* -*- c++ -*- */
/*
 * Copyright 2023 Kepeng Luan.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_MVDR_TEST_MVDR_IMPL_H
#define INCLUDED_MVDR_TEST_MVDR_IMPL_H

#include <gnuradio/mvdr_test/mvdr.h>
#include <iostream>
#include <armadillo>
#include <cmath>
#include <mat.h>
#include "matlab.h"
#define pi 3.14159265358979323846

namespace gr {
namespace mvdr_test {

class mvdr_impl : public mvdr
{
private:
    // Nothing to declare in this block.
    int num_inputs_=1;
    float sampling_frequency_;
    int taps_;
    int target_prn_;
    int ms_to_process_;

public:
    mvdr_impl(int num_inputs,
              float sampling_frequency,
              int taps,
              int target_prn,
              int ms_to_process);
    ~mvdr_impl() override;

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required) override;

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items) override;
};

} // namespace mvdr_test
} // namespace gr

#endif /* INCLUDED_MVDR_TEST_MVDR_IMPL_H */
