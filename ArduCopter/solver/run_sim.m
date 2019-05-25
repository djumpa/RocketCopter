% Simulate landing
r_0 = [50 ; 50];
v_0 = [0 ; 0];
m_0 = 10;
x_0 = [r_0; v_0 ; m_0];

r_d = [0 ; 0];
v_d = [0 ; 0];

p.phi = 0; % cant angle
p.T_max = 220; % MAX thrust
p.max_throttle = 1.0; p.min_throttle = 0.1; 
p.Isp = 225;
p.m_dry = 5; %kg
p.g = [0 ; -9.80665]; % gravity vector


% Initialize controller with GFOLD-computed trajectory
[G.tv, ~, G.r, G.v, G.u, G.m] = GFOLD(15, r_0, v_0, r_d, v_d, m_0, 35, p);
G.r_spline = spapi(4, G.tv, G.r);
G.v_spline = spapi(3, G.tv, G.v);
G.a_spline = spapi(2, G.tv, G.u);
G.m_spline = spapi(2, G.tv, G.m);
G.r1 = p.min_throttle * p.T_max * cosd(p.phi);
G.r2 = p.max_throttle * p.T_max * cosd(p.phi);
G.T_max = p.T_max;
plot_results(G.tv,G.r,G.v,G.u,G.m,9.80665,G.T_max)
