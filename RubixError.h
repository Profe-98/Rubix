#pragma once
#include <winerror.h>

//
// MessageId: RBX_SUCCESS
//
// MessageText:
//
// The Rubix library was successfully initialized.
//
#define RBX_SUCCESS _HRESULT_TYPEDEF_(0x00070001L)

//
// MessageId: RBX_FAIL
//
// MessageText:
//
// The initialization of Rubix failed.
// Look at the log files to find more information
//
#define RBX_FAIL _HRESULT_TYPEDEF_(0x80070001L)