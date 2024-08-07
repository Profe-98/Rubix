

//==
__kernel void matrix_div_scalar(global double* matrix, global double* res, const double scalar, unsigned int size)
{
    int i = get_global_id(0);
    if(i < size)
    {
        res[i] = matrix[i] / scalar;
    }
}


//==
//save it for l8r
//since one matrix cant be divided by another, we implement logic to muliply matrix A with the inverse of matrix B
__kernel void matrix_div_matrix()
{
    
}