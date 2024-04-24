using System;

class LongestCommonSubsequence
{
    public static string FindLCS(string sequence1, string sequence2)
    {
        int[,] lengths = new int[sequence1.Length + 1, sequence2.Length + 1];

        for (int i = 0; i <= sequence1.Length; i++)
        {
            for (int j = 0; j <= sequence2.Length; j++)
            {
                if (i == 0 || j == 0)
                {
                    lengths[i, j] = 0;
                }
                else if (sequence1[i - 1] == sequence2[j - 1])
                {
                    lengths[i, j] = lengths[i - 1, j - 1] + 1;
                }
                else
                {
                    lengths[i, j] = Math.Max(lengths[i - 1, j], lengths[i, j - 1]);
                }
            }
        }

        int index = lengths[sequence1.Length, sequence2.Length];
        char[] lcs = new char[index];

        int m = sequence1.Length, n = sequence2.Length;
        while (m > 0 && n > 0)
        {
            if (sequence1[m - 1] == sequence2[n - 1])
            {
                lcs[index - 1] = sequence1[m - 1];
                m--;
                n--;
                index--;
            }
            else if (lengths[m - 1, n] > lengths[m, n - 1])
            {
                m--;
            }
            else
            {
                n--;
            }
        }

        return new string(lcs);
    }

    static void Main(string[] args)
    {
        string sequence1 = "AGGTAB";
        string sequence2 = "GXTXAYB";

        string lcs = FindLCS(sequence1, sequence2);
        Console.WriteLine("Longest Common Subsequence: " + lcs);
    }
}
