%save results to csv
control_rate = 400; % Hz
control_time = 0:1/control_rate:G.tv(end);

thrust = norms(G.u).*G.m./G.T_max;
thrust_interp = interp1(G.tv,thrust,control_time);

angle = 90 - rad2deg(atan2(G.u(2,:), G.u(1,:)));
angle_interp = interp1(G.tv,angle,control_time);

vx = G.v(1,:);
vx_interp = interp1(G.tv,vx,control_time);

vz = G.v(2,:);
vz_interp = interp1(G.tv,vz,control_time);

rx = G.r(1,:);
rx_interp = interp1(G.tv,rx,control_time);

rz = G.r(2,:);
rz_interp = interp1(G.tv,rz,control_time);


csvwrite('hoverslam.csv',[thrust_interp;angle_interp;vx_interp;vz_interp;rx_interp;rz_interp]')