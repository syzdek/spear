/*
 *  $Id: $
 */
/*
 *  Syzdek's Silly Calculators
 *  Copyright (c) 2008 David M. Syzdek <david@syzdek.net>
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
/*
 *  LoanCalculator.m - computes loan information
 */
#define _SSC_SRC_LOAN_CALCULATOR_M 1
#import "LoanCalculator.h"

/////////////
//         //
//  Class  //
//         //
/////////////
@implementation LoanCalculator

- (float) apr
{
   return(apr);
}


- (void)  setApr:(float)rate;
{
   if (rate <= 0)
      return;
   apr = rate;
   interestRate = rate/ 1200;
   [self calculatePaymentAmount];
   return;
}


- (float) calculatePaymentAmount
{
   float numerator;
   float denominator;

   numerator     = interestRate * principal;
   denominator   = 1 - pow((1 + interestRate), (paymentCount * -1));
   paymentAmount = numerator / denominator;

   return(paymentAmount);
}


- (int) calculatePaymentCount
{
   float numerator;
   float denominator;

   paymentAmount = 1476.75;
   principal     = 175000.00;
   interestRate  = 0.005;

   numerator    = -1 * log(1 - ((interestRate * principal) / paymentAmount));
   denominator  = log(1 + interestRate);
   paymentCount = (int) round(numerator / denominator);

   return(paymentCount);
}


- (float) calculatePrincipal
{
   float a;
   float b;
   a = paymentAmount / interestRate;
   b = 1 - pow((1+interestRate), (paymentCount * - 1));
   principal = a * b;
   return(principal);
}


- (float) interestPaid
{
   return((paymentCount * paymentAmount) - principal);
}


- (float) interestRate
{
   return(interestRate);
}


- (void)  setInterestRate:(float)rate
{
   if (rate <= 0)
      return;
   interestRate = rate;
   apr = rate * 1200;
   [self calculatePaymentAmount];
   return;
}


- (id) init
{
   //[super init];

   [self setApr:6];
   [self setPaymentCount:360];
   [self setPrincipal:150000];

   return(self);
}


- (float) paymentAmount
{
   return(paymentAmount);
}


- (void)  setPaymentAmount:(float)payment
{
   if (payment <= 0)
      return;
   paymentAmount = payment;
   [self calculatePrincipal];
   return;
}


- (int) paymentCount
{
   return(paymentCount);
}


- (void) setPaymentCount:(int)count
{
   if (count <= 0)
      return;
   paymentCount = count;
   [self calculatePaymentAmount];
   return;
}


- (float) principal
{
   return(principal);
}


- (void) setPrincipal:(float)anAmount
{
   principal = anAmount;
   [self calculatePaymentAmount];
   return;
}


- (float) totalCost
{
   return(paymentCount * paymentAmount);
}


@end
/* end of source file */
