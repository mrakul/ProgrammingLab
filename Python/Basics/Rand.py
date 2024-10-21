# A first Python script
from math import exp
import timeit


startTime = timeit.default_timer()

# a = 0
# for i in range(999999):
#     a = a + 1

KANFunction = 1.0166*exp(-396.1934*(-0.0999*(-0.4285*500 + 0.0029*(0.2314 - 0.953)**2 + 0.4692*(0.4588 - 507)**2 - 0.2681*(0.5124 - 501)**2 - (0.7412 - 503)**2 - 0.1900*(1 - 0.8127*0.97)**2 - 0.0866*(1 - 0.5946*505)**2 + 0.8294*(-504 - 0.2556)**2 - 0.1422)**2 + 0.0365*(-0.3432*500 - 0.3685*(0.1850 - 505)**2 + 0.0490*(0.5871 - 0.953)**2 + (0.6140 - 501)**2 - 0.9895*(0.7400 - 0.97)**2 - 0.3507*(1 - 0.1585*507)**2 + 0.5480*(1 - 0.7700*504)**2 + 0.1585*(-0.9119*503 - 1)**2 + 0.4977)**2 - 0.2646*(-0.1879*(0.0452 - 0.97)**2 + 0.5048*(0.3400 - 501)**2 + (0.5267 - 504)**2 + 0.5372*(0.6562 - 0.953)**2 - 0.1469*(1 - 0.5927*505)**2 + 0.2757*(-0.2659*507 - 1)**2 - 0.1923*(-500 - 0.2116)**2 - 0.2091*(-503 - 0.4728)**2 - 0.4845)**2 - (-0.1063*(0.0813 - 504)**2 + 0.1857*(0.2488 - 507)**2 - 0.0978*(0.2721 - 0.97)**2 - 0.1341*(0.4763 - 505)**2 - 0.7589*(0.5774 - 503)**2 - (0.6125 - 501)**2 + 0.1012*(0.6268 - 0.953)**2 - 0.0586*(-500 - 0.8469)**2 + 0.4441)**2 + 0.0266)**2 + 446.8388*(-0.0123*500 - 0.0132*(0.1850 - 505)**2 + 0.0017*(0.5871 - 0.953)**2 + 0.0358*(0.6140 - 501)**2 - 0.0354*(0.7400 - 0.97)**2 - 0.0126*(1 - 0.1585*507)**2 + 0.0196*(1 - 0.7700*504)**2 + 0.0057*(-0.9119*503 - 1)**2 - 0.0429*(-0.4285*500 + 0.0029*(0.2314 - 0.953)**2 + 0.4692*(0.4588 - 507)**2 - 0.2681*(0.5124 - 501)**2 - (0.7412 - 503)**2 - 0.1900*(1 - 0.8127*0.97)**2 - 0.0866*(1 - 0.5946*505)**2 + 0.8294*(-504 - 0.2556)**2 - 0.2135)**2 + 0.3073*(-0.1879*(0.0452 - 0.97)**2 + 0.5048*(0.3400 - 501)**2 + (0.5267 - 504)**2 + 0.5372*(0.6562 - 0.953)**2 - 0.1469*(1 - 0.5927*505)**2 + 0.2757*(-0.2659*507 - 1)**2 - 0.1923*(-500 - 0.2116)**2 - 0.2091*(-503 - 0.4728)**2 - 0.2648)**2 - (-0.1063*(0.0813 - 504)**2 + 0.1857*(0.2488 - 507)**2 - 0.0978*(0.2721 - 0.97)**2 - 0.1341*(0.4763 - 505)**2 - 0.7589*(0.5774 - 503)**2 - (0.6125 - 501)**2 + 0.1012*(0.6268 - 0.953)**2 - 0.0586*(-500 - 0.8469)**2 + 0.4447)**2 + 0.0259)**2) - 0.0418
KANFunction_exp = exp(-396.1934*(-0.0999*(-0.4285*500 + 0.0029*(0.2314 - 0.953)**2 + 0.4692*(0.4588 - 507)**2 - 0.2681*(0.5124 - 501)**2 - (0.7412 - 503)**2 - 0.1900*(1 - 0.8127*0.97)**2 - 0.0866*(1 - 0.5946*505)**2 + 0.8294*(-504 - 0.2556)**2 - 0.1422)**2 + 0.0365*(-0.3432*500 - 0.3685*(0.1850 - 505)**2 + 0.0490*(0.5871 - 0.953)**2 + (0.6140 - 501)**2 - 0.9895*(0.7400 - 0.97)**2 - 0.3507*(1 - 0.1585*507)**2 + 0.5480*(1 - 0.7700*504)**2 + 0.1585*(-0.9119*503 - 1)**2 + 0.4977)**2 - 0.2646*(-0.1879*(0.0452 - 0.97)**2 + 0.5048*(0.3400 - 501)**2 + (0.5267 - 504)**2 + 0.5372*(0.6562 - 0.953)**2 - 0.1469*(1 - 0.5927*505)**2 + 0.2757*(-0.2659*507 - 1)**2 - 0.1923*(-500 - 0.2116)**2 - 0.2091*(-503 - 0.4728)**2 - 0.4845)**2 - (-0.1063*(0.0813 - 504)**2 + 0.1857*(0.2488 - 507)**2 - 0.0978*(0.2721 - 0.97)**2 - 0.1341*(0.4763 - 505)**2 - 0.7589*(0.5774 - 503)**2 - (0.6125 - 501)**2 + 0.1012*(0.6268 - 0.953)**2 - 0.0586*(-500 - 0.8469)**2 + 0.4441)**2 + 0.0266)**2 + 446.8388*(-0.0123*500 - 0.0132*(0.1850 - 505)**2 + 0.0017*(0.5871 - 0.953)**2 + 0.0358*(0.6140 - 501)**2 - 0.0354*(0.7400 - 0.97)**2 - 0.0126*(1 - 0.1585*507)**2 + 0.0196*(1 - 0.7700*504)**2 + 0.0057*(-0.9119*503 - 1)**2 - 0.0429*(-0.4285*500 + 0.0029*(0.2314 - 0.953)**2 + 0.4692*(0.4588 - 507)**2 - 0.2681*(0.5124 - 501)**2 - (0.7412 - 503)**2 - 0.1900*(1 - 0.8127*0.97)**2 - 0.0866*(1 - 0.5946*505)**2 + 0.8294*(-504 - 0.2556)**2 - 0.2135)**2 + 0.3073*(-0.1879*(0.0452 - 0.97)**2 + 0.5048*(0.3400 - 501)**2 + (0.5267 - 504)**2 + 0.5372*(0.6562 - 0.953)**2 - 0.1469*(1 - 0.5927*505)**2 + 0.2757*(-0.2659*507 - 1)**2 - 0.1923*(-500 - 0.2116)**2 - 0.2091*(-503 - 0.4728)**2 - 0.2648)**2 - (-0.1063*(0.0813 - 504)**2 + 0.1857*(0.2488 - 507)**2 - 0.0978*(0.2721 - 0.97)**2 - 0.1341*(0.4763 - 505)**2 - 0.7589*(0.5774 - 503)**2 - (0.6125 - 501)**2 + 0.1012*(0.6268 - 0.953)**2 - 0.0586*(-500 - 0.8469)**2 + 0.4447)**2 + 0.0259)**2)
KANFunction_pow = -396.1934*(-0.0999*(-0.4285*500 + 0.0029*(0.2314 - 0.953)**2 + 0.4692*(0.4588 - 507)**2 - 0.2681*(0.5124 - 501)**2 - (0.7412 - 503)**2 - 0.1900*(1 - 0.8127*0.97)**2 - 0.0866*(1 - 0.5946*505)**2 + 0.8294*(-504 - 0.2556)**2 - 0.1422)**2 + 0.0365*(-0.3432*500 - 0.3685*(0.1850 - 505)**2 + 0.0490*(0.5871 - 0.953)**2 + (0.6140 - 501)**2 - 0.9895*(0.7400 - 0.97)**2 - 0.3507*(1 - 0.1585*507)**2 + 0.5480*(1 - 0.7700*504)**2 + 0.1585*(-0.9119*503 - 1)**2 + 0.4977)**2 - 0.2646*(-0.1879*(0.0452 - 0.97)**2 + 0.5048*(0.3400 - 501)**2 + (0.5267 - 504)**2 + 0.5372*(0.6562 - 0.953)**2 - 0.1469*(1 - 0.5927*505)**2 + 0.2757*(-0.2659*507 - 1)**2 - 0.1923*(-500 - 0.2116)**2 - 0.2091*(-503 - 0.4728)**2 - 0.4845)**2 - (-0.1063*(0.0813 - 504)**2 + 0.1857*(0.2488 - 507)**2 - 0.0978*(0.2721 - 0.97)**2 - 0.1341*(0.4763 - 505)**2 - 0.7589*(0.5774 - 503)**2 - (0.6125 - 501)**2 + 0.1012*(0.6268 - 0.953)**2 - 0.0586*(-500 - 0.8469)**2 + 0.4441)**2 + 0.0266)**2 + 446.8388*(-0.0123*500 - 0.0132*(0.1850 - 505)**2 + 0.0017*(0.5871 - 0.953)**2 + 0.0358*(0.6140 - 501)**2 - 0.0354*(0.7400 - 0.97)**2 - 0.0126*(1 - 0.1585*507)**2 + 0.0196*(1 - 0.7700*504)**2 + 0.0057*(-0.9119*503 - 1)**2 - 0.0429*(-0.4285*500 + 0.0029*(0.2314 - 0.953)**2 + 0.4692*(0.4588 - 507)**2 - 0.2681*(0.5124 - 501)**2 - (0.7412 - 503)**2 - 0.1900*(1 - 0.8127*0.97)**2 - 0.0866*(1 - 0.5946*505)**2 + 0.8294*(-504 - 0.2556)**2 - 0.2135)**2 + 0.3073*(-0.1879*(0.0452 - 0.97)**2 + 0.5048*(0.3400 - 501)**2 + (0.5267 - 504)**2 + 0.5372*(0.6562 - 0.953)**2 - 0.1469*(1 - 0.5927*505)**2 + 0.2757*(-0.2659*507 - 1)**2 - 0.1923*(-500 - 0.2116)**2 - 0.2091*(-503 - 0.4728)**2 - 0.2648)**2 - (-0.1063*(0.0813 - 504)**2 + 0.1857*(0.2488 - 507)**2 - 0.0978*(0.2721 - 0.97)**2 - 0.1341*(0.4763 - 505)**2 - 0.7589*(0.5774 - 503)**2 - (0.6125 - 501)**2 + 0.1012*(0.6268 - 0.953)**2 - 0.0586*(-500 - 0.8469)**2 + 0.4447)**2 + 0.0259)**2

stopTime = timeit.default_timer()

print('Calculation Time: ', stopTime - startTime)
print('Calculation Time:  %.8f ms' % (1000 * (stopTime - startTime)))  
print(f'KANFunction: {KANFunction}, KANFunction_exp: {KANFunction_exp}, KANFunction_pow: {KANFunction_pow}')  