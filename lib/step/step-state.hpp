#ifndef PLATFORM_STEP_STATE_H
#define PLATFORM_STEP_STATE_H

#include "../parameters.hpp"
#include <algorithm>
#include <array>

namespace platform {

// TODO: it is unclear whether having all these parameters separate from just
// 0-1 really helps. In reality it is often clearer to just do the conversion in
// the instrument file because various combinations of them once you add
// "amounts" and "amount" dynamically ends up requiring the conversion again.

// TODO: 0 to 140 so that we can turn if off entirely and use the external clock only
using BPMParameter = ExponentialParameter<1.f, 240.f, 1.5f>;
//using BPMParameter = IntegerRangeParameter<30, 240>;
using StepsParameter = IntegerRangeParameter<0, 31>;
//using DestinationParameter = IntegerRangeParameter<0, 2>;
using ScaleParameter = IntegerRangeParameter<0, 6>;

using AlgorithmParameter = IntegerRangeParameter<0, 8>;

using FrequencyParameter = ExponentialParameter<27.5f, 1000.f, 3.5f>;
using CutoffParameter = ExponentialParameter<5.f, HALF_SAMPLE_RATE, 3.f>;
using DecayParameter = ExponentialParameter<0.f, 10.f, 3.f>;


struct StepState {
  BPMParameter bpm;
  RawParameter volume;
  RawParameter pitch;
  CutoffParameter cutoff;

  StepsParameter stepCount;
  DecayParameter volumeDecay;
  DecayParameter pitchDecay;
  DecayParameter cutoffDecay;

  RawParameter skips;
  RawParameter volumeAmount;
  RawParameter pitchAmount;
  RawParameter cutoffAmount;

  AlgorithmParameter algorithm;
  OverdriveParameter drive;
  ScaleParameter scale;
  RawParameter resonance;

  uint step = 0;
  std::array<float, 32> steps;  
  // TODO: make separate arrays for each destination
  std::array<float, 32> amounts;  
  std::array<float, 32> amountsBackup;  

  StepState()
    : bpm{120.f},
      volume{0},
      pitch{0},
      cutoff{16000},

      stepCount{0},
      volumeDecay{0},
      pitchDecay{0},
      cutoffDecay{0},

      algorithm{0},
      drive{0},
      scale{0},
      resonance{0},

      skips{0},
      volumeAmount{0},
      pitchAmount{0},
      cutoffAmount{0},
      
      step{0} {
    for (size_t i = 0; i < 16; i++) {
      steps[i] = 0.f;
      amounts[i] = 0.f;
      amountsBackup[i] = 0.f;
    }
  }
};

}  // namespace platform

#endif  // PLATFORM_STEP_STATE_H