# Finish matching before porting, and keep original bugs until then

No Native port work starts until all Game code is made of Matched functions. Until then, matching C reproduces the Original's behaviour exactly, including known defects such as #490, #492 and #708: a "fix" would change the bytes, and an early port would fork the source before its structure and names have settled. Confirmed defects are fixed deliberately during the port, with regression coverage.
