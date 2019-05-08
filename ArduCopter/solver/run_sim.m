% Simulate landing
r_0 = [2 ; 1.5]*1e3;
v_0 = [100 ; -75];
m_0 = 1905;
x_0 = [r_0; v_0 ; m_0];

r_d = [0 ; 0];
v_d = [0 ; 0];

p.phi = 0; % cant angle
p.T_max = 6 * 3100; % MAX thrust
p.max_throttle = 0.8; p.min_throttle = 0.3; 
p.Isp = 225;
p.m_dry = 1505; %kg
p.g = [0 ; -3.7114]; % gravity vector


% Initialize controller with GFOLD-computed trajectory
[G.tv, ~, G.r, G.v, G.u, G.m] = GFOLD(50, r_0, v_0, r_d, v_d, m_0, 180, p);
G.r_spline = spapi(4, G.tv, G.r);
G.v_spline = spapi(3, G.tv, G.v);
G.a_spline = spapi(2, G.tv, G.u);
G.m_spline = spapi(2, G.tv, G.m);
G.r1 = p.min_throttle * p.T_max * cosd(p.phi);
G.r2 = p.max_throttle * p.T_max * cosd(p.phi);

