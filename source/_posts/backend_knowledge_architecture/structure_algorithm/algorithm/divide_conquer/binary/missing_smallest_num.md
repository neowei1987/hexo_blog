Find the smallest missing number
Given a sorted array of n distinct integers where each integer is in the range from 0 to m-1 and m > n. Find the smallest number that is missing from the array.


Examples
Input: {0, 1, 2, 6, 9}, n = 5, m = 10
Output: 3




Input: {4, 5, 10, 11}, n = 4, m = 12
Output: 0


解题思路：
1. Sort. 二分查找。。关键是思考如何将问题二分掉
