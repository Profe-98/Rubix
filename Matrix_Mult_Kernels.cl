

//==
__kernel void matrix_mult_scalar(global double* matrix, global double* result, const double scalar, const uint size)
{
    int i = get_global_id(0);
    if(i < size)
    {
        result[i] = matrix[i] * scalar;
    } 
}



//==
//could hang the gpu We test this kernel at the end.
__kernel void matrix_mult_matrix(global double* matrix_l, global double* matrix_r, global double* matrix_res, const unsigned int rows_l, const unsigned int cols_l, const unsigned int cols_r, const unsigned int strides_r_l, const unsigned int strides_c_l, const unsigned int strides_r_r, const unsigned int strides_c_r, const unsigned int memsize_l, const unsigned int memsize_r)
{
    int row_l = get_global_id(0);
    int col_l = get_global_id(1);
    for(int col_r = 0; col_r < cols_r; ++col_r) // cols_l = rows_r thats why its missing
    {
        double sum = 0;
        int rep = 0;
        while(rep < cols_l)
        {
            sum += matrix_l[row_l * strides_c_l + col_l * strides_r_l] * matrix_r[col_l * strides_c_r + col_r];
            ++rep;
        }
        matrix_res[row_l * strides_c_r + col_r] = sum;
    }
}