int*** create(int d3, int d2, int d1)
{
    int*** n = new int** [d3] ();

    for (int k3 = 0; k3 < d3; ++k3) {
        n[k3] = new int* [d2] ();

        for (int k2 = 0; k2 < d2; ++k2) {
            n[k3][k2] = new int[d1]();

            for (int k1 = 0; k1 < d1; ++k1) {
                n[k3][k2][k1] = k3*d2 + k2*d1 + k1;
            }
        }
    }

    return n;
}

void destroy(int ***n, int d3, int d2, int)
{
    for (int k3 = 0; k3 < d3; ++k3) {
        for (int k2 = 0; k2 < d2; ++k2) {
            delete[] n[k3][k2];
        }
        delete[] n[k3];
    }
    delete[] n;
}

int main()
{
    int ***n = create(3, 4, 5);
    destroy(n, 3, 4, 5);
    return 0;
}