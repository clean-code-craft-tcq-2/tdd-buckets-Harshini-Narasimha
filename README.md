# Test Driven Ranges

The charging current varies during the process of charging.
We need to capture the range of current measurements -
what range of currents are most often encountered while charging.

> **DO NOT** jump into implementation! Read the example and the starting task below.

## Example

### Input

A set of periodic current samples from a charging session,
as an array of integers. For example:
`3, 3, 5, 4, 10, 11, 12`

### Functionality

The continuous ranges in there are: `3,4,5` and `10,11,12`.

The task is to detect the ranges and
output the number of readings in each range.

In this example,

- the `3-5` range has `4` readings
- the `10-12` range has `3` readings.

### Output

The expected output would be in comma-separated (csv format):

```
Range, Readings
3-5, 4
10-12, 3
```

## Tasks

Establish quality parameters: 

- What is the maximum complexity (CCN) per function? CCN =3
- How many lines of duplicate code will you tolerate? No Duplication beyond 3 lines
- Ensure 100% line and branch coverage at every step. Include the coverage yml in the workflows.

Adapt/adopt/extend the `yml` files from one of your previous workflow folders.

Start Test-driven approach

1. Write the smallest possible failing test: give input `4,5`. assert output to be `4-5, 2`.
1. Write the minimum amount of code that'll make it pass.
1. Refactor any assumptions, continue to pass this test. Do not add any code without a corresponding test.

## Assumptions

1. Input sample list should contain all positive values
2. Input sample list should not be empty

## Actions

1. Validate the Inputs
2. If inputs are valid then sort the smaples and intrepret the Ranges
3. Return the string in csv format
4. If the inputs are not valid then return 0

##Test cases:

1. Check whether the input list is Valid. Expected Results : should return true if all the values are positive integers. Else return false for invalid data.
2. Check the formatting of the range in lowerRange-upperRange format. Expected result : Compare the Actual and expected result
3. Check if range are continuous. Expected result: return true if continuous else false.
4. Check the data for 2 continuous current charging data.Expected result : Compare the Actual and expected Readings same
5. Check the sample which is empty. Expected result: Range list empty when no reading available
6. Check the data with only one input. Expected result : Compare the Actual and expected Readings and the range max and min value should be same
7. Check the data with multiple readings continuous(current charging data). Expected result : Compare the Actual and expected Readings same
8. Check the data with multiple readings non-continuous(current charging data). Expected result : Compare the Actual and expected Readings same
