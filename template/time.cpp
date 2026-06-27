auto start = chrono::high_resolution_clock::now();
auto end = chrono::high_resolution_clock::now();
cerr << "Time: " << chrono::duration<double>(end - start).count() << "s\n";