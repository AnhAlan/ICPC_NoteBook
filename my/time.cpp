auto start = chrono::high_resolution_clock::now();
auto end = chrono::high_resolution_clock::now();
auto duration = chrono::duration_cast<chrono::milliseconds>(end - start).count();
cerr << "Time: " << duration << " ms\n"; // millisecond 1000 = 1s