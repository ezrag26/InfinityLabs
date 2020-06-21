/*******************************************************************************
 * Date: 		22/10/2019
 * Developer:	Ezra Gordon
 * Reviewer:    Yossi
 * Satus: 		S
 ******************************************************************************/


#include <stdlib.h> /* strtod */
#include <string.h> /* strlen */
#include <assert.h> /* assert */
#include <math.h>   /* pow    */

#include "calculator.h"
#include "stack.h"

#define ASCII (256)
#define DO_FUNCS (7)

typedef enum
{
    WAIT_OPERANDS,
    WAIT_OPERATORS,
    ERROR
} state_t;

typedef enum
{
    /* Operators that are pushed into the operators stack */
    EMPTY,
    OPEN_PAREN,
    ADD,
    SUB,
    MULT,
    DIV,
    POW,

    /* SIMPLE, COMPLEX, and POW are used for PRECEDENCE in Calc() */
    /* SIMPLE = ADD and SUB, COMPLEX = MULT and DIV, POW = POW */
    SIMPLE = 2,
    COMPLEX = 4
} operators_t;

typedef struct calculator_s
{
    mystack_t *operands;
    mystack_t *operators;
    status_t status;
    char **exp_ptr;
} calc_t;

typedef state_t (*calc_func_t)(calc_t *);
typedef state_t (*state_func_t)(calc_t *);

state_t (*StateLUT[2][256])(calc_t *) = {{NULL}, {NULL}};
state_t (*CalcFuncLUT[DO_FUNCS])(calc_t *) = {0};

static double OperandPeek(calc_t *calc)
{
    return (*(double *)StackPeek(calc->operands));
}

static operators_t OperatorPeek(calc_t *calc)
{
    return (*(operators_t *)StackPeek(calc->operators));
}

static void OperandPop(calc_t *calc)
{
    StackPop(calc->operands);
}

static void OperatorPop(calc_t *calc)
{
    StackPop(calc->operators);
}

static void OperandPush(calc_t *calc, double *result)
{
    StackPush(calc->operands, result);
}

static void OperatorPush(calc_t *calc, operators_t *operator)
{
    StackPush(calc->operators, operator);
}

static void CalculatorDestory(calc_t *calc)
{
    StackDestroy(calc->operands);
    StackDestroy(calc->operators);
    free(calc); calc = NULL;
}

static void IncrementExpressionPtr(calc_t *calc)
{
    ++(*calc->exp_ptr);
}

static void UpdateStatus(calc_t *calc, status_t STATUS)
{
    calc->status = STATUS;
}

/*********************************** CalcAdd **********************************/

static state_t CalcAdd(calc_t *calc)
{
    double num2 = OperandPeek(calc);
    double num1 = 0.0;
    double result = 0.0;

    OperandPop(calc);
    OperatorPop(calc);

    num1 = OperandPeek(calc);
    OperandPop(calc);

    result = (num1 + num2);
    OperandPush(calc, &result);

    return (WAIT_OPERANDS);
}

/******************************** CalcSubtract ********************************/

static state_t CalcSubtract(calc_t *calc)
{
    double num2 = OperandPeek(calc);
    double num1 = 0.0;
    double result = 0.0;

    OperandPop(calc);
    OperatorPop(calc);

    num1 = OperandPeek(calc);
    OperandPop(calc);

    result = (num1 - num2);
    OperandPush(calc, &result);

    return (WAIT_OPERANDS);
}

/********************************** CalcMult **********************************/

static state_t CalcMult(calc_t *calc)
{
    double num2 = OperandPeek(calc);
    double num1 = 0.0;
    double result = 0.0;

    OperandPop(calc);
    OperatorPop(calc);

    num1 = OperandPeek(calc);
    OperandPop(calc);

    result = (num1 * num2);
    OperandPush(calc, &result);

    return (WAIT_OPERANDS);
}

/********************************* CalcDivide *********************************/

static state_t CalcDivide(calc_t *calc)
{
    double num2 = OperandPeek(calc);
    double num1 = 0.0;
    double result = 0.0;

    OperandPop(calc);
    OperatorPop(calc);

    num1 = OperandPeek(calc);
    OperandPop(calc);

    if (0 == num2)
    {
        UpdateStatus(calc, MATH_ERROR);
        return (ERROR);
    }

    result = (num1 / num2);
    OperandPush(calc, &result);

    return (WAIT_OPERANDS);
}

/********************************* CalcPower **********************************/

static state_t CalcPower(calc_t *calc)
{
    double num2 = OperandPeek(calc);
    double num1 = 0.0;
    double result = 0.0;

    OperandPop(calc);
    OperatorPop(calc);

    num1 = OperandPeek(calc);
    OperandPop(calc);

    result = pow(num1, num2);

    if (HUGE_VAL == result)
    {
        UpdateStatus(calc, MATH_ERROR);
        return (ERROR);
    }

    OperandPush(calc, &result);

    return (WAIT_OPERANDS);
}

/****************************** InitCalcFuncLUT *******************************/

static void InitCalcFuncLUT()
{
    CalcFuncLUT[0] = NULL;
    CalcFuncLUT[1] = NULL;
    CalcFuncLUT[2] = CalcAdd;
    CalcFuncLUT[3] = CalcSubtract;
    CalcFuncLUT[4] = CalcMult;
    CalcFuncLUT[5] = CalcDivide;
    CalcFuncLUT[6] = CalcPower;
}

/************************************ Calc ************************************/

static state_t Calc(calc_t *calc, operators_t PRECEDENCE)
{
    state_t state = WAIT_OPERANDS;
    operators_t OP = EMPTY;

    while (((OP = OperatorPeek(calc)) >= PRECEDENCE) && (state != ERROR))
    {
        state = CalcFuncLUT[OP](calc);
    }

    return (state);
}

/***************************** MakeSpaceOperator ******************************/

static state_t MakeSpaceOperator(calc_t *calc)
{
    IncrementExpressionPtr(calc);

    return (WAIT_OPERATORS);
}

/*********************************** GetNum ***********************************/

static state_t GetNum(calc_t *calc)
{
    const char *expression = *calc->exp_ptr;
    const char *check_ptr = expression;
    double data = strtod(expression, calc->exp_ptr);

    /* check for invalid number/characters for strtod */
    if (check_ptr == *(calc->exp_ptr))
    {
        if (' ' == **(calc->exp_ptr))
        {
            IncrementExpressionPtr(calc);
            return(WAIT_OPERANDS);
        }
        else
        {
            UpdateStatus(calc, SYNTAX_ERROR);
            return (ERROR);
        }
    }

    OperandPush(calc, &data);

    return (WAIT_OPERATORS);
}

/******************************* PushOpenParen ********************************/

static state_t PushOpenParen(calc_t *calc)
{
    operators_t open_paren = OPEN_PAREN;

    OperatorPush(calc, &open_paren);
    IncrementExpressionPtr(calc);

    return (WAIT_OPERANDS);
}

/******************************** OperandError ********************************/

static state_t OperandError(calc_t *calc)
{
    UpdateStatus(calc, SYNTAX_ERROR);
    return (ERROR);
}

/******************************* OperatorError ********************************/

static state_t OperatorError(calc_t *calc)
{
    UpdateStatus(calc, SYNTAX_ERROR);
    return (ERROR);
}

/****************************** CalcToOpenParen *******************************/

static state_t CalcToOpenParen(calc_t *calc)
{
    state_t state = Calc(calc, SIMPLE);
    state = WAIT_OPERATORS;

    if (OPEN_PAREN != OperatorPeek(calc))
    {
        UpdateStatus(calc, SYNTAX_ERROR);
        return (ERROR);
    }

    OperatorPop(calc);
    IncrementExpressionPtr(calc);

    return (state);
}

/********************************* PushAddOp **********************************/

static state_t PushAddOp(calc_t *calc)
{
    state_t state = Calc(calc, SIMPLE);
    operators_t add = ADD;

    OperatorPush(calc, &add);
    IncrementExpressionPtr(calc);

    return (state);
}

/********************************* PushSubOp **********************************/

static state_t PushSubOp(calc_t *calc)
{
    state_t state = Calc(calc, SIMPLE);
    operators_t sub = SUB;

    OperatorPush(calc, &sub);
    IncrementExpressionPtr(calc);

    return (state);
}

/********************************* PushMultOp *********************************/

static state_t PushMultOp(calc_t *calc)
{
    state_t state = Calc(calc, COMPLEX);
    operators_t mult = MULT;

    OperatorPush(calc, &mult);
    IncrementExpressionPtr(calc);

    return (state);
}

/********************************* PushDivOp **********************************/

static state_t PushDivOp(calc_t *calc)
{
    state_t state = Calc(calc, COMPLEX);
    operators_t div = DIV;

    OperatorPush(calc, &div);
    IncrementExpressionPtr(calc);

    return (state);
}

/********************************* PushPowOp **********************************/

static state_t PushPowOp(calc_t *calc)
{
    state_t state = Calc(calc, POW);
    operators_t power = POW;

    OperatorPush(calc, &power);
    IncrementExpressionPtr(calc);

    return (state);
}

/******************************* CalcReachedEnd *******************************/

static state_t CalcReachedEnd(calc_t *calc)
{
    state_t state = Calc(calc, SIMPLE);

    /* should be empty if there are no math/syntax errors */
    if (MATH_ERROR != calc->status && EMPTY != OperatorPeek(calc))
    {
        UpdateStatus(calc, SYNTAX_ERROR);
    }

    state = ERROR;

    return (state);
}

/******************************** InitStateLUT ********************************/

static void InitStateLUT()
{
    size_t i = 0;
    int valid_strtod[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
                          '+', '-', '.', ' '};

    /* functions for when waiting for operands */
    for (i = 0; i < ASCII; ++i)
    {
        StateLUT[WAIT_OPERANDS][i] = OperandError;
    }

    StateLUT[WAIT_OPERANDS]['('] = PushOpenParen;

    for (i = 0; i < ARR_SIZE(valid_strtod); ++i)
    {
        StateLUT[WAIT_OPERANDS][valid_strtod[i]] = GetNum;
    }

    /* functions for when waiting for operators */
    for (i = 0; i < ASCII; ++i)
    {
        StateLUT[WAIT_OPERATORS][i] = OperatorError;
    }

    StateLUT[WAIT_OPERATORS][0] = CalcReachedEnd;
    StateLUT[WAIT_OPERATORS][' '] = MakeSpaceOperator;
    StateLUT[WAIT_OPERATORS][')'] = CalcToOpenParen;
    StateLUT[WAIT_OPERATORS]['*'] = PushMultOp;
    StateLUT[WAIT_OPERATORS]['+'] = PushAddOp;
    StateLUT[WAIT_OPERATORS]['-'] = PushSubOp;
    StateLUT[WAIT_OPERATORS]['/'] = PushDivOp;
    StateLUT[WAIT_OPERATORS]['^'] = PushPowOp;
}

/****************************** CreateCalculator ******************************/

static calc_t *CreateCalculator(calc_t *calc, const char *expression)
{
    size_t operands_element_size = sizeof(double);
    size_t operators_element_size = sizeof(operators_t);
    size_t expression_length = 0;
    size_t operands_capacity = 0;
    size_t operators_capacity = 0;
    operators_t empty = EMPTY;

    expression_length = strlen(expression);
    operands_capacity = (expression_length / 2) + 1;
    operators_capacity = expression_length + 1;

    calc = (calc_t *)malloc(sizeof(calc_t));

    if (NULL == calc)
    {
        PRNT_ERR("Memor allocation error");
        return (NULL);
    }

    /* create operands stack */
    calc->operands = StackCreate(operands_capacity, operands_element_size);

    if (NULL == calc->operands)
    {
        PRNT_ERR("Memor allocation error");
        free(calc); calc = NULL;
        return (NULL);
    }

    /* create operators stack */
    calc->operators = StackCreate(operators_capacity, operators_element_size);

    if (NULL == calc->operators)
    {
        PRNT_ERR("Memor allocation error");
        StackDestroy(calc->operands);
        free(calc); calc = NULL;
        return (NULL);
    }

    calc->exp_ptr = (char **)&expression;

    /* push "NULL" element, for use when reaching end of expression */
    OperatorPush(calc, &empty);

    UpdateStatus(calc, SUCCESS);

    return (calc);
}

/********************************** Calculate *********************************/

status_t Calculate(const char *expression, double *result)
{
    calc_t *calc = NULL;
    state_t state = WAIT_OPERANDS;
    status_t ret_status = SUCCESS;
    int ch = 0;

    assert(NULL != expression);

    calc = CreateCalculator(calc, expression);

    if (NULL == calc)
    {
        PRNT_ERR("Memor allocation error");
        return (ALLOC_ERROR);
    }

    calc->exp_ptr = (char **)&expression;

    InitStateLUT();
    InitCalcFuncLUT();

    while (state != ERROR)
    {
        ch = (int)**calc->exp_ptr;
        state = StateLUT[state][ch](calc);
    }

    if (SUCCESS == calc->status)
    {
        *result = OperandPeek(calc);
    }
    else
    {
        *result = 0;
    }

    ret_status = calc->status;

    CalculatorDestory(calc);

    return (ret_status);
}
