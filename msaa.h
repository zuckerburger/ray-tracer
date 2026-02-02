#pragma once
#include <span>
#include <array>

struct Sample {
  double sx;
  double sy;
};

typedef enum  {
  NO_MSAA = 0,
  MSAA_2X = 2,
  MSAA_4X = 4
} MsaaOption;


constexpr std::array<Sample, 1> NO_MSAA_PATTERN = { Sample{0,0} };

constexpr std::array<Sample, 2> MSAA_2_PATTERN = {
    Sample{-4.0/16, -4.0/16},
    Sample{4.0/16, 4.0/16}
};

constexpr std::array<Sample, 4> MSAA_4_PATTERN = {
    Sample{-2.0/16, -6.0/16},
    Sample{-6.0/16, 2.0/16},
    Sample{2.0/16, 6.0/16},
    Sample{6.0/16, -2.0/16}
};

const std::span<const Sample> setMsaa(MsaaOption msaa) {
  switch (msaa) {
    case NO_MSAA:
      return NO_MSAA_PATTERN;
    case MSAA_2X:
      return MSAA_2_PATTERN;
    case MSAA_4X:
      return MSAA_4_PATTERN;
  }
  return NO_MSAA_PATTERN;
}
