def permutations(lst):
    result = []

    def backtrack(curr_permutation, remaining_elements):
        if len(curr_permutation) == len(lst):
            result.append(curr_permutation)
            return
        for i in range(len(remaining_elements)):
            next_permutation = curr_permutation + [remaining_elements[i]]
            next_remaining = remaining_elements[:i] + remaining_elements[i+1:]
            backtrack(next_permutation, next_remaining)

    backtrack([], lst)
    return result

# Example usage
input_list = [1, 2, 3]
print("All permutations of", input_list, "are:")
print(permutations(input_list))
