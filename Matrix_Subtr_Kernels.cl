

//==
__kernel void matrix_subtr_scalar(global double* matrix, global double* res, const double scalar, unsigned int size)
{
    int i = get_global_id(0);
    if(i < size)
    {
        res[i] = matrix[i] - scalar;
    }
}



//==
__kernel void matrix_subtr_matrix(global double* matrix_l, global double* matrix_r, global double* res, const unsigned int rows_l, const unsigned int rows_r, const unsigned int cols_l, const unsigned int cols_r, const unsigned int strides_r_l, const unsigned int strides_r_r, const unsigned int strides_c_l, const unsigned int strides_c_r, const unsigned int memsize_r, const unsigned int memsize_l)
{
    int x = get_global_id(0);
    int y = get_global_id(1);

    if(x < rows_l && y < cols_l)
    {
        int idx_l = x * strides_c_l + y * strides_r_l;
        int idx_r = x * strides_c_r + y * strides_r_r;

        		//Perform addition
		if(memsize_l < memsize_r)
		{
			res[idx_r] = matrix_l[idx_l] + matrix_r[idx_r]; 
		}
        else
        {
            res[idx_l] = matrix_l[idx_l] + matrix_r[idx_r];
        }
    }
}