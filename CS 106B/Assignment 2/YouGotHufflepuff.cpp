#include "YouGotHufflepuff.h"
#include "GUI/SimpleTest.h"
#include <cmath>
using namespace std;
/*This code matches a user to a another person that is
 * the most similar to them by using the users responses
 * to questions who's answers are linked to another person.
 */

//Pointer to a helper function which converts
// user picks into scores attached to each
//character
int Translate(int rating, int charInfluence);

//pointer to helper function which determines if there
//are nonzero scores for each map of characters
bool NonZerosPresent(const Map<char, int>& scores);

//this function takes in a set of questions and returns
//a random question from the set and removes it from the set
Question randomQuestionFrom(Set<Question>& questions) {
    Question random = randomElement(questions);
    questions.remove(random);
    return random;
}

/*This function takes a const Map<Question, int> which holds the user's
 * answers to personalit quiz questions and a Map<char, int> containing
 * their OCEAN(or other grading scale) score*/
Map<char, int> scoresFrom(const Map<Question, int>& answers) {
    Map<char, int> scores;
    for(Question response : answers){
        int rating = answers[response];
        for(char letter: response.factors){
            int score = response.factors[letter];
            score = Translate(rating, score);
            scores[letter] += score;
        }
    }
    return scores;
}

/*
 * This function takes an int rating which is the users answer
 * and converts it into scores attached to each character and
 * returns that score
 */
int Translate(int rating, int charInfluence){
    if(rating == 1){
        return -2*charInfluence;
    }
    if (rating ==2){
        return -1*charInfluence;
    }
    if(rating ==4){
        return 1*charInfluence;
    }
    if(rating ==5){
        return 2*charInfluence;
    }
    return 0;
}

/* This function tkes in const Map<char, int>& of the users scores and
 * outputs a Map<char, double> of the users normalized scores
 */
Map<char, double> normalize(const Map<char, int>& scores) {
    Map<char, double> normalized;
    if(!NonZerosPresent(scores))
       error("There are no non zero values pr");
    double normalizingRatio;
    for(char x: scores){
        normalizingRatio += double(scores[x] * scores[x]);
    }
    normalizingRatio = sqrt(normalizingRatio);
    for(char y: scores){
        normalized[y] = double( scores[y] / normalizingRatio);
    }
    return normalized;
}

/*This helper function takes in a Map<char, int>
 * and returns a bool if it contains nonzero keys
 * or not */
bool NonZerosPresent(const Map<char, int>& scores){
    for(char character: scores){
        if( scores[character]!= 0){
            return true;
        }
    }
    return false;
}

/*This function takes in a Map<char, double> of two people
 * and returns a double representing their similarity as
 * calculated by cosine similarity */
double cosineSimilarityOf(const Map<char, double>& lhs,
                          const Map<char, double>& rhs) {
    double similarity;
    for(char char1: lhs){
        for(char char2: rhs){
            if(char1 == char2){
                similarity += (lhs[char1] * rhs[char2]);
            }
        }
    }
    return similarity;
}

/*This function takes in a Map<char, int> of the user's answers and a
 * Set<Person> people of other people, compares each person in people
 * to the user based on the users answers, and returns which person in
 * people is most similar to the user */
Person mostSimilarTo(const Map<char, int>& scores, const Set<Person>& people) {
    if(people.isEmpty() || scores.isEmpty()){
        error("There is no one similar to you");
    }
    double mostSimilarity;
    Person mostSimilar;
    Map<char, double> normUser = normalize(scores);
    for(Person character: people){
        Map<char, double> normPerson = normalize(character.scores);
        double similarity = cosineSimilarityOf(normUser, normPerson);
        if(similarity > mostSimilarity){
            mostSimilarity = similarity;
            mostSimilar = character;
        }
    }
    return mostSimilar;
}


/* * * * *   Test Cases Below This Point   * * * * */

PROVIDED_TEST("randomQuestionFrom picks only item if there's only one choice.") {
    Question theBigOne = { "What is the meaning of life?", { } };

    Set<Question> questions = { theBigOne };

    EXPECT_EQUAL(randomQuestionFrom(questions), theBigOne);
    EXPECT_EQUAL(questions.size(), 0);
}

PROVIDED_TEST("randomQuestionFrom picks all questions given enough calls.") {
    /* Master copy */
    Set<Question> blowingInTheWind = {
        { "How many roads must a man walk down before you can call him a man?",      {{ 'O',  2 }} },
        { "How many seas must a white dove sail before she sleeps in the sand?",     {{ 'C', -1 }} },
        { "How many times must the cannonballs fly before they're forever banned?",  {{ 'E',  1 }} },
        { "How many years must a mountain exist before it is washed to the sea?",    {{ 'A', -2 }} },
        { "How many years can some people exist before they're allowed to be free?", {{ 'N',  1 }} },
    };

    /* The one we're going to pick elements from. */
    Set<Question> toPickFrom = blowingInTheWind;

    /* Pull out the questions. */
    Set<Question> picked;
    for (int i = 0; i < blowingInTheWind.size(); i++) {
        Question chosen = randomQuestionFrom(toPickFrom);

        /* This should be one of the original questions. */
        EXPECT(blowingInTheWind.contains(chosen));

        /* It should not have been chosen already. */
        EXPECT(!picked.contains(chosen));
        picked += chosen;

        /* The size of the question list should have dropped. */
        EXPECT_EQUAL(toPickFrom.size(), blowingInTheWind.size() - 1 - i);
    }

    EXPECT_EQUAL(picked, blowingInTheWind);
}

PROVIDED_TEST("randomQuestionFrom reports error on empty set of questions.") {
    Set<Question> questions;
    EXPECT_ERROR(randomQuestionFrom(questions));
}

PROVIDED_TEST("scoresFrom works on the first handout example.") {
    Map<Question, int> input = {
        {{ "I am quick to understand things.", { {'O', +1}, {'N', +1} } }, 5},
        {{ "I go my own way.",                 { {'O', +1}, {'E', -1} } }, 4},
        {{ "I know no limits.",                { {'E', +1}, {'A', -1} } }, 2},
        {{ "I become overwhelmed by events.",  { {'O', -1}, {'N', -1} } }, 1},
    };

    Map<char, int> expected = {
        { 'O', +5 },
        { 'E', -2 },
        { 'A', +1 },
        { 'N', +4 }
    };

    EXPECT_EQUAL(scoresFrom(input), expected);
}

PROVIDED_TEST("scoresFrom works on the second handout example.") {
    Map<Question, int> input = {
        {{ "I keep my thoughts to myself.",                { {'E', -1}            } }, 4},
        {{ "I show my gratitude.",                         { {'E', +1}, {'A', +1} } }, 3},
        {{ "I put off unpleasant tasks.",                  { {'C', -1},           } }, 4},
        {{ "I take an interest in other people's lives.",  { {'C', -1}, {'A', +1} } }, 4},
    };

    Map<char, int> expected = {
        { 'C', -2 },
        { 'E', -1 },
        { 'A', +1 },
    };

    EXPECT_EQUAL(scoresFrom(input), expected);
}

PROVIDED_TEST("scoresFrom works on the third handout example.") {
    Map<Question, int> input = {
        {{ "I reassure others.",       { {'C', -1}, {'A', +1} } }, 3},
        {{ "I feel others' emotions.", { {'E', +1}, {'A', +1} } }, 3},
    };

    Map<char, int> expected = {
        { 'C', 0 },
        { 'E', 0 },
        { 'A', 0 },
    };

    EXPECT_EQUAL(scoresFrom(input), expected);
}

PROVIDED_TEST("scoresFrom works with an empty set of questions.") {
    EXPECT(scoresFrom({}).isEmpty());
}

PROVIDED_TEST("scoresFrom works with non-OCEAN factor letters.") {
    Map<Question, int> input = {
        {{ "I like rainbows.", { {'R', 1}, {'O', 2}, {'Y', 3},
                                 {'G', 4}, {'B', 5}, {'I', 6},
                                 {'V', 7}, } }, 4},
        {{ "I like CS106B.",   { {'C', 1}, {'S', 2}, {'1', 3},
                                 {'0', 4}, {'6', 5}, {'B', 6}, } }, 4},
    };
    Map<char, int> expected = {
        {'R',  1},
        {'O',  2},
        {'Y',  3},
        {'G',  4},
        {'B', 11},
        {'I',  6},
        {'V',  7},
        {'C',  1},
        {'S',  2},
        {'1',  3},
        {'0',  4},
        {'6',  5}
    };

    EXPECT_EQUAL(scoresFrom(input), expected);
}

PROVIDED_TEST("normalize does not add or remove keys.") {
    Map<char, int> incomplete = {
        { 'C', 1 },
        { 'O', 1 },
        { 'N', 1 },
        { 'E', 1 }
    };

    auto result = normalize(incomplete);
    EXPECT(result.containsKey('C'));
    EXPECT(result.containsKey('O'));
    EXPECT(result.containsKey('N'));
    EXPECT(result.containsKey('E'));
    EXPECT(!result.containsKey('A'));
}

PROVIDED_TEST("normalize works on positive numbers.") {
    Map<char, int> scores = {
        { 'C', 1 },
        { 'O', 1 },
        { 'N', 1 },
        { 'E', 1 },
    };
    Map<char, double> expected = {
        { 'C', 0.5 },
        { 'O', 0.5 },
        { 'N', 0.5 },
        { 'E', 0.5 },
    };

    EXPECT_EQUAL(normalize(scores), expected);
}

PROVIDED_TEST("normalize works on negative numbers.") {
    Map<char, int> scores = {
        { 'C', -1 },
        { 'O', -1 },
        { 'N', -1 },
        { 'E', -1 },
    };
    Map<char, double> expected = {
        { 'C', -0.5 },
        { 'O', -0.5 },
        { 'N', -0.5 },
        { 'E', -0.5 },
    };

    EXPECT_EQUAL(normalize(scores), expected);
}

PROVIDED_TEST("normalize works on unequal values.") {
    Map<char, int> scores = {
        { 'O',  3 },
        { 'N', -4 },
    };
    Map<char, double> expected = {
        { 'O',  0.6 },
        { 'N', -0.8 },
    };

    EXPECT_EQUAL(normalize(scores), expected);
}

PROVIDED_TEST("normalize works on non-OCEAN inputs.") {
    Map<char, int> scores = {
        { 'C', -7 },
        { 'S', +6 },
        { '1', -3 },
        { '0', +2 },
        { '6', -2 },
        { 'B', +2 },
    };

    double norm = sqrt(106.0);

    Map<char, double> expected = {
        { 'C', -7 / norm },
        { 'S', +6 / norm },
        { '1', -3 / norm },
        { '0', +2 / norm },
        { '6', -2 / norm },
        { 'B', +2 / norm },
    };

    EXPECT_EQUAL(normalize(scores), expected);
}

PROVIDED_TEST("normalize reports errors on inputs that are all zero.") {
    EXPECT_ERROR(normalize({}));
    EXPECT_ERROR(normalize({{'A', 0}, {'C', 0}, {'E', 0}}));
}

PROVIDED_TEST("cosineSimilarityOf works with all keys present.") {
    Map<char, double> one = {
        { 'O',  1 },
        { 'C',  2 },
        { 'E',  3 },
        { 'A',  4 },
        { 'N',  5 },
    };
    Map<char, double> two = {
        { 'O', -1 },
        { 'C', -2 },
        { 'E', -3 },
        { 'A', -4 },
        { 'N', -5 },
    };
    EXPECT_EQUAL(cosineSimilarityOf(one, two), -55);
}

PROVIDED_TEST("cosineSimilarityOf works where keys are present in RHS but not LHS.") {
    Map<char, double> one = {
        { 'O',  1 },
        { 'C',  2 },
        { 'E',  3 },
        { 'A',  4 },
        { 'N',  5 },
    };
    Map<char, double> two = {
        { 'C', -2 },
        { 'E', -3 },
        { 'A', -4 },
        { 'N', -5 },
    };
    EXPECT_EQUAL(cosineSimilarityOf(one, two), -54);
}

PROVIDED_TEST("cosineSimilarityOf works where keys are present in LHS but not RHS.") {
    Map<char, double> one = {
        { 'C',  2 },
        { 'E',  3 },
        { 'A',  4 },
        { 'N',  5 },
    };
    Map<char, double> two = {
        { 'O',  1 },
        { 'C', -2 },
        { 'E', -3 },
        { 'A', -4 },
        { 'N', -5 },
    };
    EXPECT_EQUAL(cosineSimilarityOf(one, two), -54);
}

PROVIDED_TEST("cosineSimilarityOf works with keys missing from both sides.") {
    Map<char, double> one = {
        { 'C',  2 },
        { 'E',  3 },
        { 'A',  4 },
    };
    Map<char, double> two = {
        { 'O',  1 },
        { 'E', -3 },
        { 'A', -4 },
    };
    EXPECT_EQUAL(cosineSimilarityOf(one, two), -25);
}

PROVIDED_TEST("cosineSimilarityOf works with non-OCEAN keys.") {
    Map<char, int> cs106a = {
        { '1', 1 },
        { '0', 1 },
        { '6', 1 },
        { 'A', 1 }
    };

    Map<char, int> cs106b = {
        { '1', 1 },
        { '0', 1 },
        { '6', 1 },
        { 'B', 1 }
    };

    EXPECT_EQUAL(cosineSimilarityOf(normalize(cs106a), normalize(cs106b)), 0.75);
}

PROVIDED_TEST("mostSimilarTo works with perfect similarity.") {
    Person o = { "Person O", {{ 'O', 1 }} },
           c = { "Person C", {{ 'C', 1 }} },
           e = { "Person E", {{ 'E', 1 }} },
           a = { "Person A", {{ 'A', 1 }} },
           n = { "Person N", {{ 'N', 1 }} };

    EXPECT_EQUAL(mostSimilarTo({{'O', 1}}, {o, c, e, a, n}), o);
    EXPECT_EQUAL(mostSimilarTo({{'C', 1}}, {o, c, e, a, n}), c);
    EXPECT_EQUAL(mostSimilarTo({{'E', 1}}, {o, c, e, a, n}), e);
    EXPECT_EQUAL(mostSimilarTo({{'A', 1}}, {o, c, e, a, n}), a);
    EXPECT_EQUAL(mostSimilarTo({{'N', 1}}, {o, c, e, a, n}), n);
}

PROVIDED_TEST("mostSimilarTo normalizes weights.") {
    Person o1 = { "Person O1", {{ 'O', 1 }} },
           o2 = { "Person O2", {{'O', 100}, {'C', 1}}};

    EXPECT_EQUAL(mostSimilarTo({{'O', 1}}, {o1, o2}), o1);
    EXPECT_EQUAL(mostSimilarTo({{'O', 100}}, {o1, o2}), o1);
    EXPECT_EQUAL(mostSimilarTo({{'O', 500}}, {o1, o2}), o1);
}

PROVIDED_TEST("mostSimilarTo works with imperfect similarity.") {
    Person o = { "Person O", {{ 'O', 2 }, {'C', 1}} },
           c = { "Person C", {{ 'C', 2 }, {'E', 1}} },
           e = { "Person E", {{ 'E', 2 }, {'A', 1}} },
           a = { "Person A", {{ 'A', 2 }, {'N', 1}} },
           n = { "Person N", {{ 'N', 2 }, {'O', 1}} };

    EXPECT_EQUAL(mostSimilarTo({{'O', 1}}, {o, c, e, a, n}), o);
    EXPECT_EQUAL(mostSimilarTo({{'C', 1}}, {o, c, e, a, n}), c);
    EXPECT_EQUAL(mostSimilarTo({{'E', 1}}, {o, c, e, a, n}), e);
    EXPECT_EQUAL(mostSimilarTo({{'A', 1}}, {o, c, e, a, n}), a);
    EXPECT_EQUAL(mostSimilarTo({{'N', 1}}, {o, c, e, a, n}), n);
}

PROVIDED_TEST("mostSimilarTo works where best match has negative similarity.") {
    Person o1 = { "Person O1", {{ 'O', 1 }} },
           o2 = { "Person O2", {{'O', 100}, {'C', 1}}};

    EXPECT_EQUAL(mostSimilarTo({{'O', -1  }}, {o1, o2}), o2);
    EXPECT_EQUAL(mostSimilarTo({{'O', -100}}, {o1, o2}), o2);
}

PROVIDED_TEST("mostSimilarTo works on non-OCEAN scores.") {
    Person karel  = { "Karel",  {{'R', 1}, {'O', 2}, {'B', 1}, {'T', 1}} };
    Person trisha = { "Trisha", {{'T', 1}, {'R', 1}, {'I', 1}, {'S', 1}, {'H', 1}, {'A', 1}} };
    Person chris  = { "Chris",  {{'C', 1}, {'H', 1}, {'R', 1}, {'I', 1}, {'S', 1}} };
    Person jerry  = { "Jerry",  {{'J', 1}, {'E', 1}, {'R', 2}, {'Y', 1}} };

    EXPECT_EQUAL(mostSimilarTo({{'R', 1}}, {karel, trisha, chris, jerry}), jerry);
}

PROVIDED_TEST("mostSimilarTo reports errors on unnormalizable scores.") {
    Person karel  = { "Karel",  {{'R', 1}, {'O', 2}, {'B', 1}, {'T', 1}} };
    Person trisha = { "Trisha", {{'T', 1}, {'R', 1}, {'I', 1}, {'S', 1}, {'H', 1}, {'A', 1}} };
    Person chris  = { "Chris",  {{'C', 1}, {'H', 1}, {'R', 1}, {'I', 1}, {'S', 1}} };
    Person jerry  = { "Jerry",  {{'J', 1}, {'E', 1}, {'R', 2}, {'Y', 1}} };

    EXPECT_ERROR(mostSimilarTo({}, {karel, trisha, chris, jerry}));

    Person indescribable = { "Indescribable", {} };
    EXPECT_ERROR(mostSimilarTo({{'C', -1}}, { indescribable }));
}

PROVIDED_TEST("mostSimilarTo reports errors if no people are provided.") {
    EXPECT_ERROR(mostSimilarTo({}, {}));
    EXPECT_ERROR(mostSimilarTo({{'C', -1}}, {}));
}
