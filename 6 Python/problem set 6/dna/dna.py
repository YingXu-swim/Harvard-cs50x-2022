import csv
import sys

def main():
    # TODO: Check for command-line usage
    if len(sys.argv) != 3:
        print("Usage: python dna.py data.csv sequence.txt")
        exit(1)

    # TODO: Read database file into a variable
    # record everyone's dna feature
    db_dict = {}
    # record how feature is constructed
    db_key = []
    # read db
    with open(sys.argv[1], "r") as file:
        db = csv.reader(file)
        for i,row in enumerate(db):
            if i == 0:
                db_key = row[1:]
            else:
                # convert str into int
                temp = row[1:]
                temp = [int(i) for i in temp]
                # append new info into dict
                db_dict[row[0]] = temp

    # TODO: Read DNA sequence file into a variable
    # record the search string object
    seq_info = ""
    with open(sys.argv[2], "r") as file:
        seq = csv.reader(file)
        for row in seq:
            seq_info = row

    # TODO: Find longest match of each STR in DNA sequence
    search_res = []
    for k in db_key:
        search_res.append(longest_match(seq_info[0], k))

    # TODO: Check database for matching profiles
    for k in db_dict:
        if search_res == db_dict[k]:
            print(k)
            return

    print("No match")
    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
