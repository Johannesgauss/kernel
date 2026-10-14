.section .text

.macro idt_stub error, num
.global idt\num
.type idt\num, @function
idt\num:
    .if \error == 0
        pushq $0
    .endif
    push $~\num
    jmp idt_common
.endm

/* CPU Exceptions (0 - 31) */
idt_stub 0, 0
idt_stub 0, 1
idt_stub 0, 2
idt_stub 0, 3
idt_stub 0, 4
idt_stub 0, 5
idt_stub 0, 6
idt_stub 0, 7
idt_stub 1, 8
idt_stub 0, 9
idt_stub 1, 10
idt_stub 1, 11
idt_stub 1, 12
idt_stub 1, 13
idt_stub 1, 14
idt_stub 0, 15
idt_stub 0, 16
idt_stub 1, 17
idt_stub 0, 18
idt_stub 0, 19
idt_stub 0, 20
idt_stub 1, 21
idt_stub 0, 22
idt_stub 0, 23
idt_stub 0, 24
idt_stub 0, 25
idt_stub 0, 26
idt_stub 0, 27
idt_stub 0, 28
idt_stub 1, 29
idt_stub 1, 30
idt_stub 0, 31

/* Hardware IRQs & Remaining Interrupts (32 - 255) */
//idt_stub 0, 32
// TODO better architecture for it!
.extern sched_interruption
.type sched_interruption, @function
idt_stub 0, 33
idt_stub 0, 34
idt_stub 0, 35
idt_stub 0, 36
idt_stub 0, 37
idt_stub 0, 38
idt_stub 0, 39
idt_stub 0, 40
idt_stub 0, 41
idt_stub 0, 42
idt_stub 0, 43
idt_stub 0, 44
idt_stub 0, 45
idt_stub 0, 46
idt_stub 0, 47
idt_stub 0, 48
idt_stub 0, 49
idt_stub 0, 50
idt_stub 0, 51
idt_stub 0, 52
idt_stub 0, 53
idt_stub 0, 54
idt_stub 0, 55
idt_stub 0, 56
idt_stub 0, 57
idt_stub 0, 58
idt_stub 0, 59
idt_stub 0, 60
idt_stub 0, 61
idt_stub 0, 62
idt_stub 0, 63
idt_stub 0, 64
idt_stub 0, 65
idt_stub 0, 66
idt_stub 0, 67
idt_stub 0, 68
idt_stub 0, 69
idt_stub 0, 70
idt_stub 0, 71
idt_stub 0, 72
idt_stub 0, 73
idt_stub 0, 74
idt_stub 0, 75
idt_stub 0, 76
idt_stub 0, 77
idt_stub 0, 78
idt_stub 0, 79
idt_stub 0, 80
idt_stub 0, 81
idt_stub 0, 82
idt_stub 0, 83
idt_stub 0, 84
idt_stub 0, 85
idt_stub 0, 86
idt_stub 0, 87
idt_stub 0, 88
idt_stub 0, 89
idt_stub 0, 90
idt_stub 0, 91
idt_stub 0, 92
idt_stub 0, 93
idt_stub 0, 94
idt_stub 0, 95
idt_stub 0, 96
idt_stub 0, 97
idt_stub 0, 98
idt_stub 0, 99
idt_stub 0, 100
idt_stub 0, 101
idt_stub 0, 102
idt_stub 0, 103
idt_stub 0, 104
idt_stub 0, 105
idt_stub 0, 106
idt_stub 0, 107
idt_stub 0, 108
idt_stub 0, 109
idt_stub 0, 110
idt_stub 0, 111
idt_stub 0, 112
idt_stub 0, 113
idt_stub 0, 114
idt_stub 0, 115
idt_stub 0, 116
idt_stub 0, 117
idt_stub 0, 118
idt_stub 0, 119
idt_stub 0, 120
idt_stub 0, 121
idt_stub 0, 122
idt_stub 0, 123
idt_stub 0, 124
idt_stub 0, 125
idt_stub 0, 126
idt_stub 0, 127
idt_stub 0, 128
idt_stub 0, 129
idt_stub 0, 130
idt_stub 0, 131
idt_stub 0, 132
idt_stub 0, 133
idt_stub 0, 134
idt_stub 0, 135
idt_stub 0, 136
idt_stub 0, 137
idt_stub 0, 138
idt_stub 0, 139
idt_stub 0, 140
idt_stub 0, 141
idt_stub 0, 142
idt_stub 0, 143
idt_stub 0, 144
idt_stub 0, 145
idt_stub 0, 146
idt_stub 0, 147
idt_stub 0, 148
idt_stub 0, 149
idt_stub 0, 150
idt_stub 0, 151
idt_stub 0, 152
idt_stub 0, 153
idt_stub 0, 154
idt_stub 0, 155
idt_stub 0, 156
idt_stub 0, 157
idt_stub 0, 158
idt_stub 0, 159
idt_stub 0, 160
idt_stub 0, 161
idt_stub 0, 162
idt_stub 0, 163
idt_stub 0, 164
idt_stub 0, 165
idt_stub 0, 166
idt_stub 0, 167
idt_stub 0, 168
idt_stub 0, 169
idt_stub 0, 170
idt_stub 0, 171
idt_stub 0, 172
idt_stub 0, 173
idt_stub 0, 174
idt_stub 0, 175
idt_stub 0, 176
idt_stub 0, 177
idt_stub 0, 178
idt_stub 0, 179
idt_stub 0, 180
idt_stub 0, 181
idt_stub 0, 182
idt_stub 0, 183
idt_stub 0, 184
idt_stub 0, 185
idt_stub 0, 186
idt_stub 0, 187
idt_stub 0, 188
idt_stub 0, 189
idt_stub 0, 190
idt_stub 0, 191
idt_stub 0, 192
idt_stub 0, 193
idt_stub 0, 194
idt_stub 0, 195
idt_stub 0, 196
idt_stub 0, 197
idt_stub 0, 198
idt_stub 0, 199
idt_stub 0, 200
idt_stub 0, 201
idt_stub 0, 202
idt_stub 0, 203
idt_stub 0, 204
idt_stub 0, 205
idt_stub 0, 206
idt_stub 0, 207
idt_stub 0, 208
idt_stub 0, 209
idt_stub 0, 210
idt_stub 0, 211
idt_stub 0, 212
idt_stub 0, 213
idt_stub 0, 214
idt_stub 0, 215
idt_stub 0, 216
idt_stub 0, 217
idt_stub 0, 218
idt_stub 0, 219
idt_stub 0, 220
idt_stub 0, 221
idt_stub 0, 222
idt_stub 0, 223
idt_stub 0, 224
idt_stub 0, 225
idt_stub 0, 226
idt_stub 0, 227
idt_stub 0, 228
idt_stub 0, 229
idt_stub 0, 230
idt_stub 0, 231
idt_stub 0, 232
idt_stub 0, 233
idt_stub 0, 234
idt_stub 0, 235
idt_stub 0, 236
idt_stub 0, 237
idt_stub 0, 238
idt_stub 0, 239
idt_stub 0, 240
idt_stub 0, 241
idt_stub 0, 242
idt_stub 0, 243
idt_stub 0, 244
idt_stub 0, 245
idt_stub 0, 246
idt_stub 0, 247
idt_stub 0, 248
idt_stub 0, 249
idt_stub 0, 250
idt_stub 0, 251
idt_stub 0, 252
idt_stub 0, 253
idt_stub 0, 254
idt_stub 0, 255

.extern idt_handler
idt_common:
    pushq %r15
    pushq %r14
    pushq %r13
    pushq %r12
    pushq %r11
    pushq %r10
    pushq %r9
    pushq %r8
    pushq %rbp
    pushq %rdi
    pushq %rsi
    pushq %rdx
    pushq %rcx
    pushq %rbx
    pushq %rax

    cld
    // TODO: for the majority of functions, this doesn't make sense
    // Furthermore, use asm macros in the future!
    movq %rsp, %rdi
    call idt_handler

    popq %rax
    popq %rbx
    popq %rcx
    popq %rdx
    popq %rsi
    popq %rdi
    popq %rbp
    popq %r8
    popq %r9
    popq %r10
    popq %r11
    popq %r12
    popq %r13
    popq %r14
    popq %r15

    addq $16, %rsp
    iretq

.global idt_load
.type idt_load, @function
idt_load:
    lidt (%rdi)
    ret

.section .rodata
.global idt_stub_table
idt_stub_table:
    .quad idt0
    .quad idt1
    .quad idt2
    .quad idt3
    .quad idt4
    .quad idt5
    .quad idt6
    .quad idt7
    .quad idt8
    .quad idt9
    .quad idt10
    .quad idt11
    .quad idt12
    .quad idt13
    .quad idt14
    .quad idt15
    .quad idt16
    .quad idt17
    .quad idt18
    .quad idt19
    .quad idt20
    .quad idt21
    .quad idt22
    .quad idt23
    .quad idt24
    .quad idt25
    .quad idt26
    .quad idt27
    .quad idt28
    .quad idt29
    .quad idt30
    .quad idt31
    //.quad idt32
    .quad sched_interruption
    .quad idt33
    .quad idt34
    .quad idt35
    .quad idt36
    .quad idt37
    .quad idt38
    .quad idt39
    .quad idt40
    .quad idt41
    .quad idt42
    .quad idt43
    .quad idt44
    .quad idt45
    .quad idt46
    .quad idt47
    .quad idt48
    .quad idt49
    .quad idt50
    .quad idt51
    .quad idt52
    .quad idt53
    .quad idt54
    .quad idt55
    .quad idt56
    .quad idt57
    .quad idt58
    .quad idt59
    .quad idt60
    .quad idt61
    .quad idt62
    .quad idt63
    .quad idt64
    .quad idt65
    .quad idt66
    .quad idt67
    .quad idt68
    .quad idt69
    .quad idt70
    .quad idt71
    .quad idt72
    .quad idt73
    .quad idt74
    .quad idt75
    .quad idt76
    .quad idt77
    .quad idt78
    .quad idt79
    .quad idt80
    .quad idt81
    .quad idt82
    .quad idt83
    .quad idt84
    .quad idt85
    .quad idt86
    .quad idt87
    .quad idt88
    .quad idt89
    .quad idt90
    .quad idt91
    .quad idt92
    .quad idt93
    .quad idt94
    .quad idt95
    .quad idt96
    .quad idt97
    .quad idt98
    .quad idt99
    .quad idt100
    .quad idt101
    .quad idt102
    .quad idt103
    .quad idt104
    .quad idt105
    .quad idt106
    .quad idt107
    .quad idt108
    .quad idt109
    .quad idt110
    .quad idt111
    .quad idt112
    .quad idt113
    .quad idt114
    .quad idt115
    .quad idt116
    .quad idt117
    .quad idt118
    .quad idt119
    .quad idt120
    .quad idt121
    .quad idt122
    .quad idt123
    .quad idt124
    .quad idt125
    .quad idt126
    .quad idt127
    .quad idt128
    .quad idt129
    .quad idt130
    .quad idt131
    .quad idt132
    .quad idt133
    .quad idt134
    .quad idt135
    .quad idt136
    .quad idt137
    .quad idt138
    .quad idt139
    .quad idt140
    .quad idt141
    .quad idt142
    .quad idt143
    .quad idt144
    .quad idt145
    .quad idt146
    .quad idt147
    .quad idt148
    .quad idt149
    .quad idt150
    .quad idt151
    .quad idt152
    .quad idt153
    .quad idt154
    .quad idt155
    .quad idt156
    .quad idt157
    .quad idt158
    .quad idt159
    .quad idt160
    .quad idt161
    .quad idt162
    .quad idt163
    .quad idt164
    .quad idt165
    .quad idt166
    .quad idt167
    .quad idt168
    .quad idt169
    .quad idt170
    .quad idt171
    .quad idt172
    .quad idt173
    .quad idt174
    .quad idt175
    .quad idt176
    .quad idt177
    .quad idt178
    .quad idt179
    .quad idt180
    .quad idt181
    .quad idt182
    .quad idt183
    .quad idt184
    .quad idt185
    .quad idt186
    .quad idt187
    .quad idt188
    .quad idt189
    .quad idt190
    .quad idt191
    .quad idt192
    .quad idt193
    .quad idt194
    .quad idt195
    .quad idt196
    .quad idt197
    .quad idt198
    .quad idt199
    .quad idt200
    .quad idt201
    .quad idt202
    .quad idt203
    .quad idt204
    .quad idt205
    .quad idt206
    .quad idt207
    .quad idt208
    .quad idt209
    .quad idt210
    .quad idt211
    .quad idt212
    .quad idt213
    .quad idt214
    .quad idt215
    .quad idt216
    .quad idt217
    .quad idt218
    .quad idt219
    .quad idt220
    .quad idt221
    .quad idt222
    .quad idt223
    .quad idt224
    .quad idt225
    .quad idt226
    .quad idt227
    .quad idt228
    .quad idt229
    .quad idt230
    .quad idt231
    .quad idt232
    .quad idt233
    .quad idt234
    .quad idt235
    .quad idt236
    .quad idt237
    .quad idt238
    .quad idt239
    .quad idt240
    .quad idt241
    .quad idt242
    .quad idt243
    .quad idt244
    .quad idt245
    .quad idt246
    .quad idt247
    .quad idt248
    .quad idt249
    .quad idt250
    .quad idt251
    .quad idt252
    .quad idt253
    .quad idt254
    .quad idt255
