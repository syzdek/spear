/*
 *  $Id: $
 */
/*
 *  Syzdek's Silly Calculators
 *  Copyright (C) 2008 David M. Syzdek <david@syzdek.net>.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */
/** @file LoanCalculator.h  Declares the interface for LoanCalculator. */
#ifndef _SSC_SRC_LOAN_CALCULATOR_H
#define _SSC_SRC_LOAN_CALCULATOR_H 1

///////////////
//           //
//  Headers  //
//           //
///////////////

#include <math.h>

#include "SSCObject.h"


///////////////////////
//                   //
//  Class Definition //
//                   //
///////////////////////
/// This class is the model of a loan with a fixed interest rate.
@interface LoanCalculator : SSCObject
{
   // loan information
   float apr;		///< annual percentage rate
   float interestRate;	///< the adjusted interest rate per period
   float paymentAmount;	///< the amount of the payment per period
   int   paymentCount;	///< the number of equal payments required to repay loan
   float principal;	///< the original principal of loan
}

/// returns the current APR of the loan.
- (float) apr;
/// sets the new APR of the loan.
/// rate must be a float that is greater than 0.00 and less than 100.00.
- (void)  setApr:(float)rate;

- (float) calculatePaymentAmount;
- (int)   calculatePaymentCount;
- (float) calculatePrincipal;

- (id)    init;

- (float) interestPaid;

- (float) interestRate;
- (void)  setInterestRate:(float)rate;

- (float) paymentAmount;
- (void)  setPaymentAmount:(float)payment;

- (int)   paymentCount;
- (void)  setPaymentCount:(int)count;

- (float) principal;
- (void)  setPrincipal:(float)anAmount;

- (float) totalCost;

@end

#endif /* end of header */
