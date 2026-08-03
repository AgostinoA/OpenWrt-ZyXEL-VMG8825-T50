const fs = require('fs');

const inputFile = process.argv[2] || 'config.json';
const outputFile = process.argv[3] || 'config_decrypted.json';

if (!fs.existsSync(inputFile)) {
  console.error(`Error: ${inputFile} not found.`);
  process.exit(1);
}

const config = JSON.parse(fs.readFileSync(inputFile, 'utf8'));

function tryDecrypt(value) {
  if (typeof value === 'string') {
    try {
      const decoded = Buffer.from(value, 'base64').toString('utf8');
      if (/^[\x20-\x7E]*$/.test(decoded)) return decoded;
    } catch (e) {}
  }
  return value;
}

function decryptObject(obj) {
  if (Array.isArray(obj)) return obj.map(decryptObject);
  if (obj && typeof obj === 'object') {
    const result = {};
    for (const [key, value] of Object.entries(obj)) {
      result[key] = key.toLowerCase().includes('password') ? tryDecrypt(value) : decryptObject(value);
    }
    return result;
  }
  return obj;
}

const decrypted = decryptObject(config);
fs.writeFileSync(outputFile, JSON.stringify(decrypted, null, 2));
console.log(`Decrypted config saved to ${outputFile}`);
