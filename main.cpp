#include <ctime>
#include <iostream>

using namespace std;

// Returns a value from [0, 1).
inline double randomDouble()
{
    srand(time(NULL) * rand());

    return (double)rand() / (double)(RAND_MAX + 1);
}

// Randomizes the existing elements of an array.
void shuffle(int array [], size_t length)
{
    for (size_t index = 0; index < length; ++index)
    {
        size_t randomIndex = length * randomDouble();

        swap(array[index], array[randomIndex]);
    }
}

// Swaps two values.
inline void swap(int &firstValue, int &secondValue)
{
    int storedValueOfFirstValue = firstValue;

    firstValue = secondValue;
    secondValue = storedValueOfFirstValue;
}

// Returns true if the problem has been solved.
// Uses the solution presented in the video.
bool solve(int notes [], int length)
{
    // Defines the number of attempts permitted.
    size_t attemptsLimit = length / 2;

    for (size_t personIndex = 0; personIndex < length; ++personIndex)
    {
        // Initializes the number of attempts to zero.
        size_t attempts = 0;

        // The index of the current note.
        size_t currentNoteIndex = personIndex;

        // Keeps looking until the person found its note.
        while (notes[currentNoteIndex] != personIndex)
        {
            // ... Or ran out of attempts.
            if (++attempts > attemptsLimit)
            {
                return false;
            }

            currentNoteIndex = notes[currentNoteIndex];
        }
    }

    return true;
}

// Runs the simulation. Returns true for every favorable case.
bool run(int notes [], size_t length)
{
    // Shuffles the array.
    shuffle(notes, length);

    // Attempts to solve the problem.
    return solve(notes, length);
}

/* Inspired by the YouTube video "An Impossible Bet" by Minute Physics.
 * Video: https://www.youtube.com/watch?v=eivGlBKlK6M
 */
int main()
{
    // Defines the array.
    const size_t length = 100;
    int notes[length];

    // Initializes the array.
    for (size_t index = 0; index < length; ++index)
    {
        notes[index] = index;
    }

    // The number of times the program will run.
    size_t runCount;

    // Gets runCount from user input.
    cout << "How many tests would you like to run?\n>";
    cin >> runCount;

    // Counts the number of cases where the solution worked.
    size_t successCount = 0;

    // Runs the program runCount times.
    cout << "\nExecuting";

    for (size_t runIndex = 0; runIndex < runCount; ++runIndex)
    {
        if (run(notes, length))
        {
            ++successCount;
        }
    }

    // Calculates the success rate. An arithmetic exception is possible.
    double successRate = 100 * successCount / runCount;

    // Outputs the result.
    cout << "\n\nThe solution has a success rate of " << successRate << "%\n\n";

    return 0;
}
