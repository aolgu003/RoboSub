function plotStateVars( x )
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
% process inputs to function
    pn          = uu(1);             % North position (meters)
    pe          = uu(2);             % East position (meters)
    h           = -uu(3);            % altitude (meters)
    u           = uu(4);             % body velocity along x-axis (meters/s)
    v           = uu(5);             % body velocity along y-axis (meters/s)
    w           = uu(6);             % body velocity along z-axis (meters/s)
    phi         = 180/pi*uu(7);      % roll angle (degrees)   
    theta       = 180/pi*uu(8);      % pitch angle (degrees)
    psi         = 180/pi*uu(9);             % yaw angle (degrees)
    p           = 180/pi*uu(10);     % body angular rate along x-axis (degrees/s)
    q           = 180/pi*uu(11);     % body angular rate along y-axis (degrees/s)
    r           = 180/pi*uu(12);     % body angular rate along z-axis (degrees/s)

    persistent pn_handle
    persistent pe_handle
    persistent h_handle
    persistent Va_handle
    persistent alpha_handle
    persistent beta_handle
    persistent phi_handle
    persistent theta_handle
    persistent chi_handle
    persistent p_handle
    persistent q_handle
    persistent r_handle
    persistent delta_e_handle
    persistent delta_a_handle
    persistent delta_r_handle
    persistent delta_t_handle
    

  % first time function is called, initialize plot and persistent vars
    if t==0,
        figure(2), clf

        subplot(8,2,1)
        hold on
        pn_handle = graph_y_yhat_yd(t, pn, pn_hat, pn_c, 'p_n', []);
        
        subplot(8,2,2)
        hold on
        Va_handle = graph_y_yhat_yd(t, Va, Va_hat, Va_c, 'V_a', []);

        subplot(8,2,3)
        hold on
        pe_handle = graph_y_yhat_yd(t, pe, pe_hat, pe_c, 'p_e', []);

        subplot(8,2,4)
        hold on
        alpha_handle = graph_y_yhat_yd(t, alpha, alpha_hat, alpha_c, '\alpha', []);

        subplot(8,2,5)
        hold on
        h_handle = graph_y_yhat_yd(t, h, h_hat, h_c, 'h', []);

        subplot(8,2,6)
        hold on
        beta_handle = graph_y_yhat_yd(t, beta, beta_hat, beta_c, '\beta', []);

        subplot(8,2,7)
        hold on
        phi_handle = graph_y_yhat_yd(t, phi, phi_hat, phi_c, '\phi', []);
        
        subplot(8,2,8)
        hold on
        p_handle = graph_y_yhat_yd(t, p, p_hat, p_c, 'p', []);
        
        subplot(8,2,9)
        hold on
        theta_handle = graph_y_yhat_yd(t, theta, theta_hat, theta_c, '\theta', []);
        
        subplot(8,2,10)
        hold on
        q_handle = graph_y_yhat_yd(t, q, q_hat, q_c, 'q', []);
        
        subplot(8,2,11)
        hold on
        chi_handle = graph_y_yhat_yd(t, chi, chi_hat, chi_c, '\chi', []);
        
        subplot(8,2,12)
        hold on
        r_handle = graph_y_yhat_yd(t, r, r_hat, r_c, 'r', []);
        
        subplot(8,2,13)
        hold on
        delta_e_handle = graph_y(t, delta_e, [], 'b');
        ylabel('\delta_e')
        
        subplot(8,2,14)
        hold on
        delta_a_handle = graph_y(t, delta_a, [], 'b');
        ylabel('\delta_a')

        subplot(8,2,15)
        hold on
        delta_r_handle = graph_y(t, delta_r, [], 'b');
        ylabel('\delta_r')
        
        subplot(8,2,16)
        hold on
        delta_t_handle = graph_y(t, delta_t, [], 'b');
        ylabel('\delta_t')
        
    % at every other time step, redraw state variables
    else 
       graph_y_yhat_yd(t, pn, pn_hat, pn_c, 'p_n', pn_handle);
       graph_y_yhat_yd(t, pe, pe_hat, pe_c, 'p_e', pe_handle);
       graph_y_yhat_yd(t, h, h_hat, h_c, 'h', h_handle);
       graph_y_yhat_yd(t, Va, Va_hat, Va_c, 'V_a', Va_handle);
       graph_y_yhat_yd(t, alpha, alpha_hat, alpha_c, '\alpha', alpha_handle);
       graph_y_yhat_yd(t, beta, beta_hat, beta_c, '\beta', beta_handle);
       graph_y_yhat_yd(t, phi, phi_hat, phi_c, '\phi', phi_handle);
       graph_y_yhat_yd(t, theta, theta_hat, theta_c, '\theta', theta_handle);
       graph_y_yhat_yd(t, chi, chi_hat, chi_c, '\chi', chi_handle);
       graph_y_yhat_yd(t, p, p_hat, p_c, 'p', p_handle);
       graph_y_yhat_yd(t, q, q_hat, q_c, 'q', q_handle);
       graph_y_yhat_yd(t, r, r_hat, r_c, 'r', r_handle);
       graph_y(t, delta_e, delta_e_handle);
       graph_y(t, delta_a, delta_a_handle);
       graph_y(t, delta_r, delta_r_handle);
       graph_y(t, delta_t, delta_t_handle);
    end
