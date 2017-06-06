import argparse

available_ops = {'INS', 'DEL', 'SUB'}
sigma = {'A','C','G','T'}
def trans(a, ops):
    if not ops[0].isdigit():
        print('输出格式错误')
        return -1

    cnt = int(ops[0])
    ops = ops[1:]

    if len(ops) != cnt:
        print('编辑距离与操作数量不符')
        return -1
    if cnt > 50000:
        print('编辑距离超出限制')
        return -1

    tmp = [[] for i in range(len(a) + 1)]
    for op in ops:
        x = op.split()
        try:
            assert x[0] in available_ops
            pos = int(x[1])
            if x[0] == 'INS':
                assert 0 <= pos < len(a)
            else:
                assert 0 <= pos <= len(a)

            if x[0] != 'DEL':
                assert x[2] in sigma

            tmp[pos].append(x)
        except:
            print('参数不合法 {0}'.format(op))
            return -1

    ops = tmp
    res = []
    for i, c in enumerate(a):
        flag_del = False
        flag_sub = False
        char_sub = ''
        ins = []
        for op in ops[i]:
            if op[0] == 'DEL':
                if flag_del:
                    print('同一个字符不能被删除多次 {0}'.format(' '.join(op)))
                    return -1
                flag_del = True
            elif op[0] == 'SUB':
                if flag_del:
                    print('无法替换已删除的字符 {0}'.format(' '.join(op)))
                    return -1
                flag_sub = True
                char_sub = op[2]
            else:
                ins.append(op[2])
        res += ins
        if flag_del:
            pass
        elif flag_sub:
            res.append(char_sub)
        else:
            res.append(c)

    for op in ops[len(a)]:
        res.append(op[2])

    return ''.join(res)

def check(dbg, s, k):
    for i in range(0, len(s) - k):
        if s[i: i + k] not in dbg:
            return False

    return True

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('-i', metavar='infile')
    parser.add_argument('-o', metavar='outfile')
    args = parser.parse_args()

    with open(args.i, 'r') as infile:
        ilines = infile.readlines()
        ilines = [x.strip() for x in ilines]
        ilines = [x for x in ilines if x]
    with open(args.o, 'r') as ansfile:
        olines = ansfile.readlines()
        olines = [x.strip() for x in olines]
        olines = [x for x in olines if x]

    if len(ilines) == 2:
        a = ilines[0]
        b = ilines[1]
        ta = trans(a, olines)

        if ta != -1:
            if ta == b:
                print(olines[0])
                print('Success')
                exit(0)
            else:
                print('编辑过程错误')
                exit(-1)
        else:
            exit(-1)
    else:
        a = ilines[0]
        cnt = int(ilines[1])
        dbg = set()
        for i in range(cnt):
            dbg.add(ilines[2 + i])
        k = len(ilines[2])
        b = olines[0]
        if not b.isupper():
            print('输出格式错误')
            exit(-1)
        if not check(dbg, b, k):
            print('输出字符串不在图上')
            exit(-1)

        ta = trans(a, olines[1:])

        if ta != -1:
            if ta == b:
                print(olines[1])
                print('Success')
                exit(0)
            else:
                print('编辑过程错误')
                exit(-1)



