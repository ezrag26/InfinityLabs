// 1.
// memcpy: copies from src to dest, but doesn't deal with overlap
// memmove: copies from src to dest, and does deal with overlap

// 2.
char *memmove(char *dest, const char* src, size_t n)
{
    char *buffer = new char[8 + 1];
    const char* src_p = src;
    char* dest_p = dest;
    size_t bytes_left = n;

    while (bytes_left >= 8)
    {
        std::strcpy(buffer, src_ptr);
        src_ptr += 8;
        // *src_ptr = '\0';
        // ++src_ptr;
        
        std::strcpy(dest_ptr, buffer);
        dest_ptr += 8;

        bytes_left -= 8;
    }

    while (bytes_left > 0)
    {
        *dest_ptr = *src_ptr;

        ++dest_ptr;
        ++src_ptr;

        --bytes_left;
    }

    delete[] buffer;

    return dest;
}