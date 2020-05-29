import zlib
import io
import shutil

def decompress(data):
        try:
            return zlib.decompress(data)
        except zlib.error:
            return decompress_corrupted(data)

def decompress_corrupted():
    f = open('data.zlib', 'rb')
    d = zlib.decompressobj(zlib.MAX_WBITS | 32)
    # f = io.StringIO(data.encode())
    result_str = b''
    buffer = f.read(1)
    try:
        while buffer:
            result_str += d.decompress(buffer)
            buffer = f.read(1)
    except zlib.error as e:
        print(f"Error zlib: {e}")
        pass
    with open('output', 'ab') as out:
        out.write(result_str)
    return result_str

# with open('data.zlib', 'rb') as f:
    # dump = f.read()
# result = decompress_corrupted()
# print(result)

# output_filename = "myzip_tester"
# dir_name = "test_folder"

# shutil.make_archive(output_filename, 'zip', dir_name)

with open('_SecureBackup.exe.extracted/28D9.zlib', 'rb') as f:
    data = f.read()
    print(data)
    result = zlib.decompress(data)
    print(result)