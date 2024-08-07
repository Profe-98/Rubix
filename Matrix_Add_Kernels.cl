__kernel void matrix_add_scalar(__global double* matrix, __global double* result, const double scalar, const unsigned int size)
{
	int i = get_global_id(0);
	if(i < size)
	{
		result[i] = matrix[i] + scalar;
	}
}


//==
__kernel void matrix_add_matrix(__global double* matrix_lhs,  __global double* matrix_rhs, __global double* result, const int rows, const int cols,  const int stride_r_lhs, const int stride_c_lhs,  const int stride_r_rhs, const int stride_c_rhs, const unsigned int memsize_lhs, const unsigned int memsize_rhs)
{
	int row = get_global_id(0);
	int col = get_global_id(1);
	if(row < rows && col < cols)
	{
		//Calculate mem Index for both matrices each
		int idx_LHS = row* stride_c_lhs + col * stride_r_lhs;
		int idx_RHS = row* stride_c_rhs + col * stride_r_rhs;


		//Perform addition
		if(memsize_lhs < memsize_rhs)
		{
			result[idx_RHS] = matrix_lhs[idx_LHS] + matrix_rhs[idx_RHS]; 
		}
		result[idx_LHS] = matrix_lhs[idx_LHS] + matrix_rhs[idx_RHS];
	}
}