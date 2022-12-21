

PRIME = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19

def MonkeyMove(monkey_id, object_worry):
	w = object_worry
	next_monkey = -1
	if (monkey_id == 0):
		w *= 17
		next_monkey = 2 if ((w % 2) == 0) else 6
	elif monkey_id == 1:
		w *= w
		next_monkey = 0 if ((w % 7) == 0) else 2

	elif monkey_id == 2:
		w += 7
		next_monkey = 7 if ((w % 13) == 0) else 6

	elif monkey_id == 3:
		w += 4
		next_monkey = 4 if ((w % 5) == 0) else 5

	elif monkey_id == 4:
		w += 5
		next_monkey = 1 if ((w % 3) == 0) else 5

	elif monkey_id == 5:
		w += 6
		next_monkey = 1 if ((w % 19) == 0) else 0

	elif monkey_id == 6:
		w *= 13
		next_monkey = 3 if ((w % 11) == 0) else 7

	elif monkey_id == 7:
		w += 2
		next_monkey = 4 if ((w % 17) == 0) else 3

	w = w % PRIME
	return {"next_owner" : next_monkey, "next_worry" : w}

ROUNDS = 10000
MONKE_COUNT = 8

monkeys = [
      [85, 79, 63, 72],
      [53, 94, 65, 81, 93, 73, 57, 92],
      [62, 63],
      [57, 92, 56],
      [67],
      [85, 56, 66, 72, 57, 99],
      [86, 65, 98, 97, 69],
      [87, 68, 92, 66, 91, 50, 68],
]

inspects = [0 for i in range(MONKE_COUNT)]
ct = 0 
while (ct < ROUNDS):
	ct += 1
	print(ct)

	for i in range(MONKE_COUNT):
		for item in monkeys[i]:
			inspects[i]+=1
			res = MonkeyMove(i, item)
			monkeys[res["next_owner"]].append(res["next_worry"])
			monkeys[i] = []

inspects.sort()
print(inspects)
print (inspects[-1] * inspects[-2])