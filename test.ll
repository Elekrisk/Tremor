declare i64 @strlen(i8* nocapture) nounwind
declare i8* @malloc(i64) nounwind
declare i8* @memcpy(i8* nocapture, i8* nocapture, i64) nounwind
declare i8* @strcat(i8* nocapture, i8* nocapture) nounwind
declare void @free(i8* nocapture) nounwind
declare i32 @printf(i8* nocapture, ...) nounwind

%cString = type { i64, i8* }

define void @"MString;!constr.char*"(%cString* %this, i8* %str) nounwind
{
	%1 = getelementptr %cString, %cString* %this, i64 0, i32 0
	%2 = getelementptr %cString, %cString* %this, i64 0, i32 1
	store i64 0, i64* %1
	%3 = inttoptr i64 0 to i8*
	store i8* %3, i8** %2
	
	
	%4 = call i64 @strlen(i8* %str)
	%5 = add i64 %4, 1
	store i64 %5, i64* %1
	
	%6 = call i8* @malloc(i64 128)
	store i8* %6, i8** %2
	
	%7 = load i8*, i8** %2
	%8 = load i64, i64* %1
	call i8* @memcpy(i8* %7, i8* %str, i64 %8)
	ret void
a:	
	ret void
}

define void @"MString;!destr"(%cString* %this) nounwind
{
	%1 = getelementptr %cString, %cString* %this, i64 0, i32 1
	%2 = load i8*, i8** %1
	%3 = ptrtoint i8* %2 to i64
	%4 = icmp eq i64 %3, 0
	br i1 %4, label %a, label %b
	
a:	; If %2 [self.ptr] is zero
	ret void
b:	; If %2 [self.ptr] isn't zero
	call void @free(i8* %2)
	ret void
}

define i8* @"MString;getPtr"(%cString* %this) nounwind
{
	%1 = getelementptr %cString, %cString* %this, i64 0, i32 1
	%2 = load i8*, i8** %1
	ret i8* %2
}

define i64 @"MString;getSize"(%cString* %this) nounwind
{
	%1 = getelementptr %cString, %cString* %this, i64 0, i32 0
	%2 = load i64, i64* %1
	ret i64 %2
}

define %cString* @"MString;!op+"(%cString* %left, %cString* %right)
{
	%left.local = alloca %cString
	%right.local = alloca %cString
	
	%1 = load %cString, %cString* %left
	store %cString %1, %cString* %left.local
	
	%2 = load %cString, %cString* %left
	store %cString %1, %cString* %right.local
	
	%s1 = call i8* @"MString;getPtr"(%cString* %left.local)
	%s2 = call i8* @"MString;getPtr"(%cString* %right.local)

	%3 = call i64 @"MString;getSize"(%cString* %left.local)
	%4 = call i64 @"MString;getSize"(%cString* %right.local)
	%5 = add i64 %3, %4
	%totSize = add i64 %5, 1
	
	%res = call i8* @malloc(i64 %totSize)
	
	%6 = call i64 @"MString;getSize"(%cString* %left.local)
	call i8* @memcpy(i8* %res, i8* %s1, i64 %6)
	
	call i8* @strcat(i8* %res, i8* %s2)
	
	%9 = call i8* @malloc(i64 128)
	%10 = bitcast i8* %9 to %cString*
	call void @"MString;!constr.char*"(%cString* %10, i8* %res)
	ret %cString* %10
}

@.str0 = private unnamed_addr constant [9 x i8] c"Hello :D\00"
@.str1 = private unnamed_addr constant [7 x i8] c"%s: %d\00"

define i32 @main()
{
	%1 = call i8* @malloc(i64 128)
	%local.str = bitcast i8* %1 to %cString*
	%2 = getelementptr [9 x i8], [9 x i8]* @.str0, i64 0, i64 0
	call void @"MString;!constr.char*"(%cString* %local.str, i8* %2)
	;asfafe
	%3 = call i8* @"MString;getPtr"(%cString * %local.str)
	%4 = call i64 @"MString;getSize"(%cString * %local.str)
	%5 = getelementptr [7 x i8], [7 x i8]* @.str1, i64 0, i64 0
	call i32 (i8*, ...) @printf(i8* %5, i8* %3, i64 %4)
	ret i32 0
}