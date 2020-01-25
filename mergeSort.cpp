int B[1000];
void MergeSortRec( float *A, int N )
{
  int M, k, i = 0, j = N / 2;

  if (N < 2) 
    return;
  M = N / 2;
  MergeSortRec( A, M );
  MergeSortRec( A + M, N - M );
  
  for (k = 0; k < N; k++)
    if (j >= N || i < M && A[i] < A[j])
      B[k] = A[i++];
    else
      B[k] = A[j++];

  for (k = 0; k < N; k++)
    A[k] = B[k];
}
/*void MergeSort(float *A, int N)
{
  B = malloc(sizeof(float) * N);
  if (B == NULL)
    return;
  MergeSortRec( A, N );
  free(B);
}
*/
