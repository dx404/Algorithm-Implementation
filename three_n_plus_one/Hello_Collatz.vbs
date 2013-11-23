Sub Hello_Collatz()
    ' Author: Duo Donald Zhao 
    ' My Maiden code in VBA!!
    ' An Excel VBA demo to illustrate the 3n+1 problem
    ' The Memoization technique does not work well by utilizing cell copying
    ' VBA Basic operations, flow control, cell copying.
    Dim maxTarget As Integer
    Dim startSeqCol As Integer
    Dim isMemo As Boolean
    maxTarget = 100
    startSeqCol = 3
    isMemo = False
    
    Dim i As Integer, j As Integer  ' Mostly duck typing, variable declarations may be omitted
    For i = 1 To maxTarget
        Cells(i, 1).Value = i
        Cells(i, startSeqCol).Value = i
        j = startSeqCol + 1
        Dim last As Integer
        last = Cells(i, j - 1).Value
        Do While last > 1
            If isMemo And last < i Then
                remainSize = Cells(last, 2).Value
                Cells(last, startSeqCol + 1).Resize(1, remainSize - 1).Copy
                Cells(i, j).Select
                ActiveSheet.Paste
                j = j + remainSize - 1
                Exit Do
            ElseIf (last Mod 2 = 1) Then
                Cells(i, j).Value = 3 * last + 1
            Else
                Cells(i, j).Value = last / 2
            End If
            last = Cells(i, j).Value
            j = j + 1 ' No ++, += operators in VBA
        Loop
        Cells(i, 2).Value = j - startSeqCol
    Next i
    Cells(1, 2).Resize(maxTarget, 1).Interior.Color = RGB(255, 255, 0)
End Sub
