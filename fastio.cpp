char buf[1 << 17];

char read()
{
    static int idx = 1 << 17, nidx = 1 << 17;
    if (idx == nidx)
    {
        nidx = fread(buf, 1, 1 << 17, stdin);
        if (!nidx)
            return 0;
        idx = 0;
    }
    return buf[idx++];
}


int readInt() {
    int ret = 0, flg = 1;
    char now = read();

    while (isspace(now)) now = read();
    if (now == '-') flg = -1, now = read();
    while (now >= 48 && now <= 57) {
        ret = ret * 10 + now - 48;
        now = read();
    }
    return ret * flg;
}