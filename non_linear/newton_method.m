function X=NewtonSist(F, JF, X0, tol, iter)
	V =PLU( JF(X0), F(X0) );
	X1 = X0 - V;
	n = 1;
	while norm( X1 - X0, 1) > tol & n <= iter
		X0 = X1;
		V = PLU( JF(X0), F(X0) );
		X1 = X0 - V;
		n += 1
	end
	X = X1
end

% F = @(X)[X(1)^2+X(2)^2-1; X(1)^2 -X(2)]
% x^3 - y = 0
% -x + y^3 = 0