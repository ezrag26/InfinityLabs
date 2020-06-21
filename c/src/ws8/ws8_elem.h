#ifndef __WS8_ELEM_H__
#define __WS8_ELEM_H__

typedef enum {INT, FLOAT, STRING} element_types_t;

typedef enum {SUCCESS, ALLOCATION_ERROR} return_val_t;

typedef struct element_features_t
{
	void *p_elem;
	
	struct functions_t
	{
		return_val_t (*print)();
		return_val_t (*add)();
		return_val_t (*free)();
	} elem_funcs_t;

} element_t;

return_val_t InitElem(void *elem, element_types_t type, element_t *p);



#endif /* __WS8_ELEM_H__ */
