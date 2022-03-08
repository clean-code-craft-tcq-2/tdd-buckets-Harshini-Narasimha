#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include "test/catch.hpp"

TEST_CASE("Output the number of readings where the current measurements have 2 continuous current charging data") {
  std::vector<int> chargingCurrentSampleList = {4,5};
  std::map<std::string, int> expectedOutputRange = {{"4-5", 2}};
  REQUIRE(getCurrentReadingsFromRanges(chargingCurrentSampleList) == expectedOutputRange);
}
