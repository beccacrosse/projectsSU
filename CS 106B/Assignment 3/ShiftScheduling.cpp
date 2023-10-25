#include "ShiftScheduling.h"
#include "GUI/SimpleTest.h"
#include "vector.h"
#include "error.h"
#include "set.h"
#include "shift.h"
using namespace std;

/* TODO: Refer to ShiftScheduling.h for more information about what this function should do.
 * Then, delete this comment.
 */

//points to shiftPossible function
bool shiftPossible(const Shift& posShift, const Set<Shift>& shiftsTaken, const int& maxHours);

Set<Shift> mostProfit(Set<Shift> bestValue, const Set<Shift>& schedule);


Set<Shift> highestValueScheduleRec(const Set<Shift> shifts, const int maxHours,
                                   const Set<Shift>& shiftsTaken){
    if(shifts.size() == 0){
        return shiftsTaken;
    }
    else{
        Shift shift = shifts.first();
        Set<Shift> takeShift;
        Set<Shift> ignoreShift = highestValueScheduleRec(shifts - shift, maxHours, shiftsTaken);
        if(shiftPossible(shift, shiftsTaken, maxHours)){
            takeShift = highestValueScheduleRec(shifts - shift, maxHours - lengthOf(shift),
                                                shiftsTaken + shift);
        }
        return mostProfit(takeShift, ignoreShift);
    }
}

bool shiftPossible(const Shift& posShift, const Set<Shift>& shiftsTaken, const int& maxHours){
    double hours = maxHours - lengthOf(posShift);
    if(hours < 0){
        return false;
    }
    if(!shiftsTaken.isEmpty()){
        for(Shift theShift: shiftsTaken){
            if(overlapsWith(theShift, posShift)){
                return false;
            }
        }
    }
    return true;
}

Set<Shift> mostProfit(Set<Shift> schedule1, const Set<Shift>& schedule2){
    if(schedule1.isEmpty()){
        return schedule2;
    }else if(schedule2.isEmpty()){
        return schedule1;
    }
    else{
        int profit1 = 0;
        int profit2 = 0;
        for(Shift shift1: schedule1){
            profit1 += valueOf(shift1);
        }
        for(Shift shift2: schedule2){
            profit2 += valueOf(shift2);
        }
        if(profit1 >= profit2){
            return schedule1;
        }
        return schedule2;
    }
}


Set<Shift> highestValueScheduleFor(const Set<Shift>& shifts, int maxHours) {
    /* TODO: Delete the next few lines and implement this function.
    (void) shifts;
    (void) maxHours;
    return {}; */
    if(maxHours <0){
        error(" Out of Bounds");
    }else{
        return highestValueScheduleRec(shifts, maxHours, {});
    }
}






/* * * * * * Test Cases * * * * * */

/* TODO: Add your own tests here. You know the drill - look for edge cases, think about
 * very small and very large cases, etc.
 */














/* * * * * * Test cases from the starter files below this point. * * * * * */

/* This nice utility function lets you call highestValueScheduleFor, passing in
 * a Vector of shifts rather than a Set. This makes it a bit easier to test things.
 * You shouldn't need this function outside of these test cases.
 */
Set<Shift> asSet(const Vector<Shift>& shifts) {
    Set<Shift> result;
    for (Shift s: shifts) {
        result += s;
    }
    return result;
}

PROVIDED_TEST("Pick only shift if you have time for it.") {
    Set<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
    };

    EXPECT(highestValueScheduleFor(shifts, 24).size() == 1);
    EXPECT(highestValueScheduleFor(shifts, 24) == shifts);
}

PROVIDED_TEST("Don't pick only shift if ou don't have time for it.") {
    Set<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday, 9AM - 5PM, value is 1000
    };

    EXPECT(highestValueScheduleFor(shifts, 3).isEmpty());
}

PROVIDED_TEST("Don't pick overlapping shifts.") {
    Vector<Shift> shifts = {
        { Day::MONDAY, 9, 17, 1000 },  // Monday,  9AM - 5PM, value is 1000
        { Day::MONDAY, 8, 18, 2000 },  // Monday, 10AM - 6PM, value is 2000
    };

    EXPECT(highestValueScheduleFor(asSet(shifts), 100).size() == 1);
    EXPECT(highestValueScheduleFor(asSet(shifts), 100).contains(shifts[1]));
}

PROVIDED_TEST("Passes the example from the handout.") {
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27 *
        { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28 *
        { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25 *
        { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
        { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
        { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
        { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
        { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
        { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
        { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
        { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
        { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
        { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
        { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
        { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25 *
    };

    /* Get back the solution. */
    Set<Shift> computedSolution = highestValueScheduleFor(asSet(shifts), 20);

    /* Form the correct answer. It's the starred entries. */
    Set<Shift> actualSolution = {
        shifts[0], shifts[1], shifts[2], shifts[14]
    };

    EXPECT(computedSolution == actualSolution);
}

PROVIDED_TEST("Handles no shifts.") {
    EXPECT(highestValueScheduleFor({}, 137).isEmpty());
}

PROVIDED_TEST("Reports an error with negative hours.") {
    /* From the handout */
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27
        { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28
        { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25
        { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
        { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
        { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
        { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
        { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
        { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
        { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
        { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
        { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
        { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
        { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
        { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25
    };

    /* Should be an error. */
    EXPECT_ERROR(highestValueScheduleFor(asSet(shifts), -1));

    /* Still an error even if there are no shifts. */
    EXPECT_ERROR(highestValueScheduleFor({}, -1));
}

PROVIDED_TEST("Handles zero free hours.") {
    /* From the handout */
    Vector<Shift> shifts = {
        { Day::MONDAY,     8, 12, 27 },  // Mon  8AM - 12PM, value 27
        { Day::MONDAY,    12, 16, 28 },  // Mon 12PM -  4PM, value 28
        { Day::MONDAY,    16, 20, 25 },  // Mon  4PM -  8PM, value 25
        { Day::MONDAY,     8, 14, 39 },  // Mon  8AM -  2PM, value 39
        { Day::MONDAY,    14, 20, 31 },  // Mon  2PM -  8PM, value 31
        { Day::TUESDAY,    8, 12,  7 },  // Tue  8AM - 12PM, value  7
        { Day::TUESDAY,   12, 16,  7 },  // Tue 12PM -  4PM, value  7
        { Day::TUESDAY,   16, 20, 11 },  // Tue  4PM -  8PM, value 11
        { Day::TUESDAY,    8, 14, 10 },  // Tue  8AM -  2PM, value 10
        { Day::TUESDAY,   14, 20,  8 },  // Tue  2PM -  8PM, value  8
        { Day::WEDNESDAY,  8, 12, 10 },  // Wed  8AM - 12PM, value 10
        { Day::WEDNESDAY, 12, 16, 11 },  // Wed 12PM -  4PM, value 11
        { Day::WEDNESDAY, 16, 20, 13 },  // Wed  4PM -  8PM, value 13
        { Day::WEDNESDAY,  8, 14, 19 },  // Wed  8AM -  2PM, value 19
        { Day::WEDNESDAY, 14, 20, 25 },  // Wed  2PM -  8PM, value 25
    };

    /* Shouldn't be an error if time is zero - that means we just don't pick anything. */
    EXPECT(highestValueScheduleFor(asSet(shifts), 0).isEmpty());
}

PROVIDED_TEST("Stress test: Don't generate shift combinations with overlapping shifts.") {
    /* All of these shifts overlap one another. If you try producing all combinations
     * of these shifts and only check at the end whether they're valid, you'll be
     * checking 2^100 ~= 10^30 combinations of shifts, which will take so long the
     * sun will have burnt out before you're finished.
     *
     * Instead, as you're going through your decision tree and building up your shifts,
     * make sure not to include any shifts that clearly conflict with something you
     * picked earlier.
     */
    Set<Shift> trickySet;
    for (int i = 0; i < 100; i++) {
        trickySet += Shift{ Day::MONDAY, 1, 2, i };
    }
    EXPECT_EQUAL(trickySet.size(), 100);

    auto result = highestValueScheduleFor(trickySet, 1);
    EXPECT_EQUAL(result.size(), 1);
}

PROVIDED_TEST("Stress test: Don't generate shift combinations that exceed time limits.") {
    /* Here's a collection of one shift per hour of the week. Your worker has exactly
     * one hour free. If you try all possible combinations of these shifts, ignoring time
     * constraints, you will have to check over 2^100 = 10^30 combinations, which will
     * take longer than the length of the known universe to process.
     *
     * Instead, as you're exploring the decision tree to generate shift combinations,
     * make sure not to add shifts that would exceed the time limit.
     */
    Set<Shift> trickySet;
    for (Day day: { Day::SUNDAY,
                    Day::MONDAY,
                    Day::TUESDAY,
                    Day::WEDNESDAY,
                    Day::THURSDAY,
                    Day::FRIDAY,
                    Day::SATURDAY}) {
        for (int start = 0; start < 24; start++) {
            trickySet += Shift{ day, start, start + 1, 10 };
        }
    }
    EXPECT_EQUAL(trickySet.size(), 7 * 24);

    auto result = highestValueScheduleFor(trickySet, 1);
    EXPECT_EQUAL(result.size(), 1);
}
