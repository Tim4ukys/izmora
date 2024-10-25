db = { }

a = 30

k = (math.pi/2) / a
for i = 0, a*4 do 
	t = k*i
	db[i] = { 
		x = t,  
		y = math.sin(t),
		err_x = 0.025,
		err_y = 0.01
	}
end

