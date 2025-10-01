% Quantize to 16-bit integers (Q15 format)
q_factor = 2^15;
quantized_coefficients = round(fir_coefficients_v1_column * q_factor);

% Write to a C header file
fid = fopen('fir_coeffs.h', 'w');
fprintf(fid, '#ifndef FIR_COEFFS_H\n');
fprintf(fid, '#define FIR_COEFFS_H\n\n');
fprintf(fid, '#define N_TAPS %d\n', length(quantized_coefficients));
fprintf(fid, 'typedef int coeff_t;\n\n');
fprintf(fid, 'const coeff_t fir_coeffs[N_TAPS] = {\n');
fprintf(fid, '  %d,\n', quantized_coefficients(1:end-1));
fprintf(fid, '  %d\n};\n\n', quantized_coefficients(end));
fprintf(fid, '#endif // FIR_COEFFS_H\n');
fclose(fid);