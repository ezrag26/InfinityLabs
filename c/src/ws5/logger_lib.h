#ifndef __LOGGER_LIB_H__
#define __LOGGER_LIB_H__

enum action_return_t {SUCCESS, EXIT, FILE_NAME_ERROR, FGETS_ERROR, 
					  FILE_OPEN_ERROR, FPUTS_ERROR, APPEND_ERROR, REMOVE_ERROR, 
					  RENAME_ERROR};

/******************************************************************************/
/***************************** Comparison Functions ***************************/
/******************************************************************************/
int StrCmp(const char *s1, const char *s2);

int PrependCmp(const char *s1, const char *s2);

int Always(const char *s1, const char *s2);


/******************************************************************************/
/****************************** Action Functions ******************************/
/******************************************************************************/
enum action_return_t Remove(char *string, const char *file_name);

enum action_return_t Count(char *string, const char *file_name);

enum action_return_t Exit(char *string, const char *file_name);

enum action_return_t Prepend(char *string, const char *file_name);

enum action_return_t Append(char *string, const char *file_name);

#endif /* __LOGGER_LIB_H__ */
