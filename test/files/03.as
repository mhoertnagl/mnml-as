# Some comment.
# Across multiple lines.
  psh 0x1234  # Push 0x1234.
  dup         # Duplicate.
  add         # Add - this is the same as multiplication by 2.
# Loop never exits.
@loop
  psh &loop
  # Some comment in-between.
  jmp