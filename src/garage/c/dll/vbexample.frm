VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "VBExample"
   ClientHeight    =   3570
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4680
   LinkTopic       =   "Form1"
   ScaleHeight     =   3570
   ScaleWidth      =   4680
   StartUpPosition =   3  'Windows Default
   Begin VB.Frame Frame2 
      Caption         =   "Returning *char"
      Height          =   1335
      Left            =   120
      TabIndex        =   5
      Top             =   1920
      Width           =   4335
      Begin VB.CommandButton Command4 
         Caption         =   "Reset"
         Height          =   375
         Left            =   2160
         TabIndex        =   8
         Top             =   840
         Width           =   735
      End
      Begin VB.CommandButton Command3 
         Caption         =   "Set"
         Height          =   375
         Left            =   1320
         TabIndex        =   7
         Top             =   840
         Width           =   735
      End
      Begin VB.Label pointer 
         Alignment       =   2  'Center
         Caption         =   "Label2"
         Height          =   255
         Left            =   120
         TabIndex        =   6
         Top             =   360
         Width           =   4095
      End
   End
   Begin VB.Frame Frame1 
      Caption         =   "Returning Long Int"
      Height          =   1335
      Left            =   120
      TabIndex        =   0
      Top             =   240
      Width           =   4335
      Begin VB.CommandButton Command2 
         Caption         =   "Reset"
         Height          =   375
         Left            =   2160
         TabIndex        =   4
         Top             =   840
         Width           =   735
      End
      Begin VB.CommandButton Command1 
         Caption         =   "Add"
         Height          =   375
         Left            =   1320
         TabIndex        =   3
         Top             =   840
         Width           =   735
      End
      Begin VB.Label sum 
         Height          =   255
         Left            =   2280
         TabIndex        =   2
         Top             =   480
         Width           =   375
      End
      Begin VB.Label Label1 
         Alignment       =   1  'Right Justify
         Caption         =   "123  +  123  ="
         Height          =   255
         Left            =   720
         TabIndex        =   1
         Top             =   480
         Width           =   1455
      End
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Option Explicit

' Holds Pointer returned by libexample.dll
Dim Handle As Long
Dim Message As String

' Lists functions we plan on calling from libexample.dll
Private Declare Function helloworld _
Lib "C:\CVSTree\examples\c\dll\Debug\libexample.dll" ( _
) As Long
   
Private Declare Function example_stringcreate _
Lib "C:\CVSTree\examples\c\dll\Debug\libexample.dll" ( _
) As Long

Private Declare Function example_stringdestroy _
Lib "C:\CVSTree\examples\c\dll\Debug\libexample.dll" ( _
    ByRef Handle As Long _
) As Long

Private Declare Function example_sum _
Lib "C:\CVSTree\examples\c\dll\Debug\libexample.dll" ( _
    ByVal Num1 As Long, _
    ByVal Num2 As Long _
) As Long
    
Private Sub Command1_Click()
'Dim Num1 As Long
'Dim Num2 As Long
Dim ExitCode As Long
ExitCode = example_sum(123, 123)
sum.Caption = Str$(ExitCode)
End Sub

Private Sub Command2_Click()
sum.Caption = Str$(0)
End Sub

Private Sub Command3_Click()
Handle = example_stringcreate()
Message = Handle
pointer.Caption = Message
End Sub

Private Sub Command4_Click()
Dim ExitCode As Long
ExitCode = example_stringdestroy(Handle)
pointer.Caption = Message
End Sub

Private Sub Form_Load()
pointer.Caption = Message
End Sub

