for power in range(1,6):
	f = open('in{0}'.format(10**power), 'w')
	for value in range(10**power):
		f.write('S {0} 0 0 0 0\n'.format(value))
		f.write('HIT {0} 0 0\n'.format(value))
	f.write('EXIT'.format(value))
	f.close()