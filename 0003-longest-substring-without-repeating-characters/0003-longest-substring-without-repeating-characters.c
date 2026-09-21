int lengthOfLongestSubstring(char* s) {
    int last[256];
    
    for (int i = 0; i < 256; i++)
        last[i] = -1;

    int left = 0;
    int maxLength = 0;

    for (int right = 0; s[right] != '\0'; right++) {
        unsigned char c = s[right];

        if (last[c] >= left)
            left = last[c] + 1;

        last[c] = right;

        int length = right - left + 1;

        if (length > maxLength)
            maxLength = length;
    }

    return maxLength;
}