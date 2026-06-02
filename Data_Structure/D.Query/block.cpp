const int maxn = 1e6 + 5;
int blockSize, numBlock, pos;
int blockSt[maxn], blockEn[maxn];
int blockId[maxn], blockPos[maxn];
void init(){
   int n;
   cin >> n;
   vector<int> a(n);
   for(int &x : a) cin >> x;
   blockSize = 0;
   numBlock = 0;
   pos = 0;
   while(blockSize * blockSize < n) blockSize++; // can build block with query size
   while(pos < n){
      numBlock++;
      blockSt[numBlock] = pos + 1;
      blockEn[numBlock] = min(pos + blockSize, n);
      pos += blockSize;
      int tmp = 0;
      for(int i = blockSt[numBlock]; i <= blockEn[numBlock]; i++){
         blockId[i] = numBlock;
         blockPos[i] = ++tmp;
      }
   }
   /*
      if build block with query
      each block has [add, get, add]
      for i = 1 -> numBlock
         for j = blockSt[i] -> blockEn[i]
            if query[j] == get
               process
                  for k = blockSt[i] -> k < j
                     process ADD
               process get with add
            cout << ans
         after block j done -> process update add (O(log n))
         after j done -> i++ 
   */
}
// process build block with array
void solve(int l, int r){
   if(blockId[l] == blockId[r]){
      // l r same block -> brute force
      for(int i = l; i <= r; i++){

      }
      return;
   }
   //process block l
   for(int i = l; i <= blockEn[blockId[l]]; i++){

   }
   //process block middle 
   for(int i = blockId[l] + 1; i <= blockId[r] - 1; i++){

   }
   //process block r
   for(int i = blockSt[blockId[r]]; i <= r; i++){

   }
}
